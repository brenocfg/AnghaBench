#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/ * ops; } ;
struct nand_chip {TYPE_2__ dummy_controller; int /*<<< orphan*/  setup_data_interface; int /*<<< orphan*/  waitfunc; int /*<<< orphan*/  dev_ready; int /*<<< orphan*/  cmd_ctrl; int /*<<< orphan*/  read_word; int /*<<< orphan*/  write_byte; int /*<<< orphan*/  read_byte; int /*<<< orphan*/  select_chip; } ;
struct TYPE_5__ {TYPE_3__* parent; } ;
struct mtd_info {char* name; TYPE_1__ dev; } ;
struct denali_nand_info {TYPE_3__* dev; int /*<<< orphan*/  max_banks; scalar_t__ clk_x_rate; scalar_t__ clk_rate; int /*<<< orphan*/  host_write; int /*<<< orphan*/  host_read; int /*<<< orphan*/  active_bank; int /*<<< orphan*/  irq; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  complete; scalar_t__ reg; struct nand_chip nand; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  DENALI_INVALID_BANK ; 
 int /*<<< orphan*/  DENALI_NAND_NAME ; 
 int ENODEV ; 
 scalar_t__ FEATURES ; 
 int FEATURES__INDEX_ADDR ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  denali_clear_irq_all (struct denali_nand_info*) ; 
 int /*<<< orphan*/  denali_cmd_ctrl ; 
 int /*<<< orphan*/  denali_controller_ops ; 
 int /*<<< orphan*/  denali_dev_ready ; 
 int /*<<< orphan*/  denali_direct_read ; 
 int /*<<< orphan*/  denali_direct_write ; 
 int /*<<< orphan*/  denali_disable_irq (struct denali_nand_info*) ; 
 int /*<<< orphan*/  denali_enable_irq (struct denali_nand_info*) ; 
 int /*<<< orphan*/  denali_hw_init (struct denali_nand_info*) ; 
 int /*<<< orphan*/  denali_indexed_read ; 
 int /*<<< orphan*/  denali_indexed_write ; 
 int /*<<< orphan*/  denali_isr ; 
 int /*<<< orphan*/  denali_read_byte ; 
 int /*<<< orphan*/  denali_read_word ; 
 int /*<<< orphan*/  denali_reset_banks (struct denali_nand_info*) ; 
 int /*<<< orphan*/  denali_select_chip ; 
 int /*<<< orphan*/  denali_setup_data_interface ; 
 int /*<<< orphan*/  denali_waitfunc ; 
 int /*<<< orphan*/  denali_write_byte ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 int devm_request_irq (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct denali_nand_info*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int ioread32 (scalar_t__) ; 
 int mtd_device_register (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_cleanup (struct nand_chip*) ; 
 int nand_scan (struct mtd_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_set_flash_node (struct nand_chip*,int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int denali_init(struct denali_nand_info *denali)
{
	struct nand_chip *chip = &denali->nand;
	struct mtd_info *mtd = nand_to_mtd(chip);
	u32 features = ioread32(denali->reg + FEATURES);
	int ret;

	mtd->dev.parent = denali->dev;
	denali_hw_init(denali);

	init_completion(&denali->complete);
	spin_lock_init(&denali->irq_lock);

	denali_clear_irq_all(denali);

	ret = devm_request_irq(denali->dev, denali->irq, denali_isr,
			       IRQF_SHARED, DENALI_NAND_NAME, denali);
	if (ret) {
		dev_err(denali->dev, "Unable to request IRQ\n");
		return ret;
	}

	denali_enable_irq(denali);
	denali_reset_banks(denali);
	if (!denali->max_banks) {
		/* Error out earlier if no chip is found for some reasons. */
		ret = -ENODEV;
		goto disable_irq;
	}

	denali->active_bank = DENALI_INVALID_BANK;

	nand_set_flash_node(chip, denali->dev->of_node);
	/* Fallback to the default name if DT did not give "label" property */
	if (!mtd->name)
		mtd->name = "denali-nand";

	chip->select_chip = denali_select_chip;
	chip->read_byte = denali_read_byte;
	chip->write_byte = denali_write_byte;
	chip->read_word = denali_read_word;
	chip->cmd_ctrl = denali_cmd_ctrl;
	chip->dev_ready = denali_dev_ready;
	chip->waitfunc = denali_waitfunc;

	if (features & FEATURES__INDEX_ADDR) {
		denali->host_read = denali_indexed_read;
		denali->host_write = denali_indexed_write;
	} else {
		denali->host_read = denali_direct_read;
		denali->host_write = denali_direct_write;
	}

	/* clk rate info is needed for setup_data_interface */
	if (denali->clk_rate && denali->clk_x_rate)
		chip->setup_data_interface = denali_setup_data_interface;

	chip->dummy_controller.ops = &denali_controller_ops;
	ret = nand_scan(mtd, denali->max_banks);
	if (ret)
		goto disable_irq;

	ret = mtd_device_register(mtd, NULL, 0);
	if (ret) {
		dev_err(denali->dev, "Failed to register MTD: %d\n", ret);
		goto cleanup_nand;
	}

	return 0;

cleanup_nand:
	nand_cleanup(chip);
disable_irq:
	denali_disable_irq(denali);

	return ret;
}