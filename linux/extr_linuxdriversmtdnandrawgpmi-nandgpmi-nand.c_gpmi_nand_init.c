#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * ops; } ;
struct nand_chip {TYPE_5__ dummy_controller; int /*<<< orphan*/  options; int /*<<< orphan*/  block_markbad; int /*<<< orphan*/ * badblock_pattern; int /*<<< orphan*/  write_buf; int /*<<< orphan*/  read_buf; int /*<<< orphan*/  read_byte; int /*<<< orphan*/  dev_ready; int /*<<< orphan*/  cmd_ctrl; int /*<<< orphan*/  setup_data_interface; int /*<<< orphan*/  select_chip; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct mtd_info {char* name; TYPE_1__ dev; } ;
struct TYPE_9__ {int payload_size; int auxiliary_size; } ;
struct gpmi_nand_data {int current_chip; int swap_block_mark; TYPE_4__ bch_geometry; TYPE_3__* pdev; int /*<<< orphan*/  dev; struct nand_chip nand; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_8__ {TYPE_2__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPMI_IS_MX23 (struct gpmi_nand_data*) ; 
 scalar_t__ GPMI_IS_MX6 (struct gpmi_nand_data*) ; 
 int /*<<< orphan*/  NAND_NO_SUBPAGE_WRITE ; 
 int gpmi_alloc_dma_buffer (struct gpmi_nand_data*) ; 
 int /*<<< orphan*/  gpmi_bbt_descr ; 
 int /*<<< orphan*/  gpmi_block_markbad ; 
 int /*<<< orphan*/  gpmi_cmd_ctrl ; 
 int /*<<< orphan*/  gpmi_dev_ready ; 
 int /*<<< orphan*/  gpmi_free_dma_buffer (struct gpmi_nand_data*) ; 
 int /*<<< orphan*/  gpmi_nand_controller_ops ; 
 int /*<<< orphan*/  gpmi_read_buf ; 
 int /*<<< orphan*/  gpmi_read_byte ; 
 int /*<<< orphan*/  gpmi_select_chip ; 
 int /*<<< orphan*/  gpmi_setup_data_interface ; 
 int /*<<< orphan*/  gpmi_write_buf ; 
 int mtd_device_register (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nand_boot_init (struct gpmi_nand_data*) ; 
 int /*<<< orphan*/  nand_cleanup (struct nand_chip*) ; 
 int nand_create_bbt (struct nand_chip*) ; 
 int nand_scan (struct mtd_info*,int) ; 
 int /*<<< orphan*/  nand_set_controller_data (struct nand_chip*,struct gpmi_nand_data*) ; 
 int /*<<< orphan*/  nand_set_flash_node (struct nand_chip*,int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static int gpmi_nand_init(struct gpmi_nand_data *this)
{
	struct nand_chip *chip = &this->nand;
	struct mtd_info  *mtd = nand_to_mtd(chip);
	int ret;

	/* init current chip */
	this->current_chip	= -1;

	/* init the MTD data structures */
	mtd->name		= "gpmi-nand";
	mtd->dev.parent		= this->dev;

	/* init the nand_chip{}, we don't support a 16-bit NAND Flash bus. */
	nand_set_controller_data(chip, this);
	nand_set_flash_node(chip, this->pdev->dev.of_node);
	chip->select_chip	= gpmi_select_chip;
	chip->setup_data_interface = gpmi_setup_data_interface;
	chip->cmd_ctrl		= gpmi_cmd_ctrl;
	chip->dev_ready		= gpmi_dev_ready;
	chip->read_byte		= gpmi_read_byte;
	chip->read_buf		= gpmi_read_buf;
	chip->write_buf		= gpmi_write_buf;
	chip->badblock_pattern	= &gpmi_bbt_descr;
	chip->block_markbad	= gpmi_block_markbad;
	chip->options		|= NAND_NO_SUBPAGE_WRITE;

	/* Set up swap_block_mark, must be set before the gpmi_set_geometry() */
	this->swap_block_mark = !GPMI_IS_MX23(this);

	/*
	 * Allocate a temporary DMA buffer for reading ID in the
	 * nand_scan_ident().
	 */
	this->bch_geometry.payload_size = 1024;
	this->bch_geometry.auxiliary_size = 128;
	ret = gpmi_alloc_dma_buffer(this);
	if (ret)
		goto err_out;

	chip->dummy_controller.ops = &gpmi_nand_controller_ops;
	ret = nand_scan(mtd, GPMI_IS_MX6(this) ? 2 : 1);
	if (ret)
		goto err_out;

	ret = nand_boot_init(this);
	if (ret)
		goto err_nand_cleanup;
	ret = nand_create_bbt(chip);
	if (ret)
		goto err_nand_cleanup;

	ret = mtd_device_register(mtd, NULL, 0);
	if (ret)
		goto err_nand_cleanup;
	return 0;

err_nand_cleanup:
	nand_cleanup(chip);
err_out:
	gpmi_free_dma_buffer(this);
	return ret;
}