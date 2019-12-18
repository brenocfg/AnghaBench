#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
struct vchiq_state {int dummy; } ;
struct vchiq_slot_zero {int* platform_data; } ;
struct vchiq_drvdata {int cache_line_size; struct rpi_firmware* fw; } ;
struct rpi_firmware {int dummy; } ;
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
typedef  scalar_t__ dma_addr_t ;
typedef  int /*<<< orphan*/  channelbase ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_IRQPOLL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MAX_FRAGMENTS ; 
 int PAGE_ALIGN (int) ; 
 int PAGE_SIZE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPI_FIRMWARE_VCHIQ_INIT ; 
 int TOTAL_SLOTS ; 
 size_t VCHIQ_PLATFORM_FRAGMENTS_COUNT_IDX ; 
 size_t VCHIQ_PLATFORM_FRAGMENTS_OFFSET_IDX ; 
 int VCHIQ_SLOT_SIZE ; 
 scalar_t__ VCHIQ_SUCCESS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct vchiq_state*) ; 
 int dma_set_mask_and_coherent (struct device*,int /*<<< orphan*/ ) ; 
 void* dmam_alloc_coherent (struct device*,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int g_cache_line_size ; 
 struct device* g_dev ; 
 char* g_fragments_base ; 
 int g_fragments_size ; 
 char* g_free_fragments ; 
 int /*<<< orphan*/  g_free_fragments_sema ; 
 int /*<<< orphan*/  g_regs ; 
 struct vchiq_drvdata* platform_get_drvdata (struct platform_device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rpi_firmware_property (struct rpi_firmware*,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vchiq_arm_log_level ; 
 int /*<<< orphan*/  vchiq_call_connected_callbacks () ; 
 int /*<<< orphan*/  vchiq_doorbell_irq ; 
 struct vchiq_slot_zero* vchiq_init_slots (void*,int) ; 
 scalar_t__ vchiq_init_state (struct vchiq_state*,struct vchiq_slot_zero*) ; 
 int /*<<< orphan*/  vchiq_log_info (int /*<<< orphan*/ ,char*,struct vchiq_slot_zero*,scalar_t__*) ; 

int vchiq_platform_init(struct platform_device *pdev, struct vchiq_state *state)
{
	struct device *dev = &pdev->dev;
	struct vchiq_drvdata *drvdata = platform_get_drvdata(pdev);
	struct rpi_firmware *fw = drvdata->fw;
	struct vchiq_slot_zero *vchiq_slot_zero;
	struct resource *res;
	void *slot_mem;
	dma_addr_t slot_phys;
	u32 channelbase;
	int slot_mem_size, frag_mem_size;
	int err, irq, i;

	/*
	 * VCHI messages between the CPU and firmware use
	 * 32-bit bus addresses.
	 */
	err = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32));

	if (err < 0)
		return err;

	g_cache_line_size = drvdata->cache_line_size;
	g_fragments_size = 2 * g_cache_line_size;

	/* Allocate space for the channels in coherent memory */
	slot_mem_size = PAGE_ALIGN(TOTAL_SLOTS * VCHIQ_SLOT_SIZE);
	frag_mem_size = PAGE_ALIGN(g_fragments_size * MAX_FRAGMENTS);

	slot_mem = dmam_alloc_coherent(dev, slot_mem_size + frag_mem_size,
				       &slot_phys, GFP_KERNEL);
	if (!slot_mem) {
		dev_err(dev, "could not allocate DMA memory\n");
		return -ENOMEM;
	}

	WARN_ON(((unsigned long)slot_mem & (PAGE_SIZE - 1)) != 0);

	vchiq_slot_zero = vchiq_init_slots(slot_mem, slot_mem_size);
	if (!vchiq_slot_zero)
		return -EINVAL;

	vchiq_slot_zero->platform_data[VCHIQ_PLATFORM_FRAGMENTS_OFFSET_IDX] =
		(int)slot_phys + slot_mem_size;
	vchiq_slot_zero->platform_data[VCHIQ_PLATFORM_FRAGMENTS_COUNT_IDX] =
		MAX_FRAGMENTS;

	g_fragments_base = (char *)slot_mem + slot_mem_size;

	g_free_fragments = g_fragments_base;
	for (i = 0; i < (MAX_FRAGMENTS - 1); i++) {
		*(char **)&g_fragments_base[i*g_fragments_size] =
			&g_fragments_base[(i + 1)*g_fragments_size];
	}
	*(char **)&g_fragments_base[i * g_fragments_size] = NULL;
	sema_init(&g_free_fragments_sema, MAX_FRAGMENTS);

	if (vchiq_init_state(state, vchiq_slot_zero) != VCHIQ_SUCCESS)
		return -EINVAL;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	g_regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(g_regs))
		return PTR_ERR(g_regs);

	irq = platform_get_irq(pdev, 0);
	if (irq <= 0)
		return irq;

	err = devm_request_irq(dev, irq, vchiq_doorbell_irq, IRQF_IRQPOLL,
			       "VCHIQ doorbell", state);
	if (err) {
		dev_err(dev, "failed to register irq=%d\n", irq);
		return err;
	}

	/* Send the base address of the slots to VideoCore */
	channelbase = slot_phys;
	err = rpi_firmware_property(fw, RPI_FIRMWARE_VCHIQ_INIT,
				    &channelbase, sizeof(channelbase));
	if (err || channelbase) {
		dev_err(dev, "failed to set channelbase\n");
		return err ? : -ENXIO;
	}

	g_dev = dev;
	vchiq_log_info(vchiq_arm_log_level,
		"vchiq_init - done (slots %pK, phys %pad)",
		vchiq_slot_zero, &slot_phys);

	vchiq_call_connected_callbacks();

	return 0;
}