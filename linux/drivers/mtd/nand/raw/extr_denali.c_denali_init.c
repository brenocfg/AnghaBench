#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * ops; } ;
struct denali_controller {int revision; int nbanks; int dma_avail; int caps; int oob_skip_bytes; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; scalar_t__ reg; int /*<<< orphan*/  host_write; int /*<<< orphan*/  host_read; int /*<<< orphan*/  setup_dma; int /*<<< orphan*/  active_bank; int /*<<< orphan*/  chips; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  complete; TYPE_1__ controller; } ;

/* Variables and functions */
 scalar_t__ CHIP_ENABLE_DONT_CARE ; 
 int CHIP_EN_DONT_CARE__FLAG ; 
 int DENALI_CAP_DMA_64BIT ; 
 int DENALI_DEFAULT_OOB_SKIP_BYTES ; 
 int /*<<< orphan*/  DENALI_INVALID_BANK ; 
 int /*<<< orphan*/  DENALI_NAND_NAME ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 scalar_t__ ECC_ENABLE ; 
 int ECC_ENABLE__FLAG ; 
 scalar_t__ FEATURES ; 
 int FEATURES__DMA ; 
 int FEATURES__INDEX_ADDR ; 
 int /*<<< orphan*/  FEATURES__N_BANKS ; 
 int FIELD_GET (int /*<<< orphan*/ ,int) ; 
 int GENMASK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ RB_PIN_ENABLED ; 
 scalar_t__ REVISION ; 
 scalar_t__ SPARE_AREA_MARKER ; 
 scalar_t__ SPARE_AREA_SKIP_BYTES ; 
 scalar_t__ TRANSFER_SPARE_REG ; 
 int /*<<< orphan*/  denali_clear_irq_all (struct denali_controller*) ; 
 int /*<<< orphan*/  denali_controller_ops ; 
 int /*<<< orphan*/  denali_direct_read ; 
 int /*<<< orphan*/  denali_direct_write ; 
 int /*<<< orphan*/  denali_enable_irq (struct denali_controller*) ; 
 int /*<<< orphan*/  denali_indexed_read ; 
 int /*<<< orphan*/  denali_indexed_write ; 
 int /*<<< orphan*/  denali_isr ; 
 int /*<<< orphan*/  denali_setup_dma32 ; 
 int /*<<< orphan*/  denali_setup_dma64 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int devm_request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct denali_controller*) ; 
 int dma_set_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 void* ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  nand_controller_init (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int swab16 (void*) ; 

int denali_init(struct denali_controller *denali)
{
	u32 features = ioread32(denali->reg + FEATURES);
	int ret;

	nand_controller_init(&denali->controller);
	denali->controller.ops = &denali_controller_ops;
	init_completion(&denali->complete);
	spin_lock_init(&denali->irq_lock);
	INIT_LIST_HEAD(&denali->chips);
	denali->active_bank = DENALI_INVALID_BANK;

	/*
	 * The REVISION register may not be reliable. Platforms are allowed to
	 * override it.
	 */
	if (!denali->revision)
		denali->revision = swab16(ioread32(denali->reg + REVISION));

	denali->nbanks = 1 << FIELD_GET(FEATURES__N_BANKS, features);

	/* the encoding changed from rev 5.0 to 5.1 */
	if (denali->revision < 0x0501)
		denali->nbanks <<= 1;

	if (features & FEATURES__DMA)
		denali->dma_avail = true;

	if (denali->dma_avail) {
		int dma_bit = denali->caps & DENALI_CAP_DMA_64BIT ? 64 : 32;

		ret = dma_set_mask(denali->dev, DMA_BIT_MASK(dma_bit));
		if (ret) {
			dev_info(denali->dev,
				 "Failed to set DMA mask. Disabling DMA.\n");
			denali->dma_avail = false;
		}
	}

	if (denali->dma_avail) {
		if (denali->caps & DENALI_CAP_DMA_64BIT)
			denali->setup_dma = denali_setup_dma64;
		else
			denali->setup_dma = denali_setup_dma32;
	}

	if (features & FEATURES__INDEX_ADDR) {
		denali->host_read = denali_indexed_read;
		denali->host_write = denali_indexed_write;
	} else {
		denali->host_read = denali_direct_read;
		denali->host_write = denali_direct_write;
	}

	/*
	 * Set how many bytes should be skipped before writing data in OOB.
	 * If a non-zero value has already been set (by firmware or something),
	 * just use it. Otherwise, set the driver's default.
	 */
	denali->oob_skip_bytes = ioread32(denali->reg + SPARE_AREA_SKIP_BYTES);
	if (!denali->oob_skip_bytes) {
		denali->oob_skip_bytes = DENALI_DEFAULT_OOB_SKIP_BYTES;
		iowrite32(denali->oob_skip_bytes,
			  denali->reg + SPARE_AREA_SKIP_BYTES);
	}

	iowrite32(0, denali->reg + TRANSFER_SPARE_REG);
	iowrite32(GENMASK(denali->nbanks - 1, 0), denali->reg + RB_PIN_ENABLED);
	iowrite32(CHIP_EN_DONT_CARE__FLAG, denali->reg + CHIP_ENABLE_DONT_CARE);
	iowrite32(ECC_ENABLE__FLAG, denali->reg + ECC_ENABLE);
	iowrite32(0xffff, denali->reg + SPARE_AREA_MARKER);

	denali_clear_irq_all(denali);

	ret = devm_request_irq(denali->dev, denali->irq, denali_isr,
			       IRQF_SHARED, DENALI_NAND_NAME, denali);
	if (ret) {
		dev_err(denali->dev, "Unable to request IRQ\n");
		return ret;
	}

	denali_enable_irq(denali);

	return 0;
}