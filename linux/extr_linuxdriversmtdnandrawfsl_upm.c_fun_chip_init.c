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
typedef  int /*<<< orphan*/  u64 ;
struct resource {scalar_t__ start; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct mtd_info {int /*<<< orphan*/  name; TYPE_2__ dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  algo; int /*<<< orphan*/  mode; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev_ready; int /*<<< orphan*/  select_chip; TYPE_1__ ecc; int /*<<< orphan*/  write_buf; int /*<<< orphan*/  read_buf; int /*<<< orphan*/  read_byte; int /*<<< orphan*/  chip_delay; int /*<<< orphan*/  cmd_ctrl; int /*<<< orphan*/  IO_ADDR_W; int /*<<< orphan*/  IO_ADDR_R; } ;
struct fsl_upm_nand {int mchip_count; scalar_t__* rnb_gpio; TYPE_3__ chip; int /*<<< orphan*/  dev; int /*<<< orphan*/  chip_delay; int /*<<< orphan*/  io_base; } ;
struct device_node {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NAND_ECC_HAMMING ; 
 int /*<<< orphan*/  NAND_ECC_SOFT ; 
 int /*<<< orphan*/  fun_chip_ready ; 
 int /*<<< orphan*/  fun_cmd_ctrl ; 
 int /*<<< orphan*/  fun_read_buf ; 
 int /*<<< orphan*/  fun_read_byte ; 
 int /*<<< orphan*/  fun_select_chip ; 
 int /*<<< orphan*/  fun_write_buf ; 
 int /*<<< orphan*/  kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int mtd_device_register (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nand_scan (struct mtd_info*,int) ; 
 int /*<<< orphan*/  nand_set_flash_node (TYPE_3__*,struct device_node*) ; 
 struct mtd_info* nand_to_mtd (TYPE_3__*) ; 
 struct device_node* of_get_next_child (struct device_node const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static int fun_chip_init(struct fsl_upm_nand *fun,
			 const struct device_node *upm_np,
			 const struct resource *io_res)
{
	struct mtd_info *mtd = nand_to_mtd(&fun->chip);
	int ret;
	struct device_node *flash_np;

	fun->chip.IO_ADDR_R = fun->io_base;
	fun->chip.IO_ADDR_W = fun->io_base;
	fun->chip.cmd_ctrl = fun_cmd_ctrl;
	fun->chip.chip_delay = fun->chip_delay;
	fun->chip.read_byte = fun_read_byte;
	fun->chip.read_buf = fun_read_buf;
	fun->chip.write_buf = fun_write_buf;
	fun->chip.ecc.mode = NAND_ECC_SOFT;
	fun->chip.ecc.algo = NAND_ECC_HAMMING;
	if (fun->mchip_count > 1)
		fun->chip.select_chip = fun_select_chip;

	if (fun->rnb_gpio[0] >= 0)
		fun->chip.dev_ready = fun_chip_ready;

	mtd->dev.parent = fun->dev;

	flash_np = of_get_next_child(upm_np, NULL);
	if (!flash_np)
		return -ENODEV;

	nand_set_flash_node(&fun->chip, flash_np);
	mtd->name = kasprintf(GFP_KERNEL, "0x%llx.%s", (u64)io_res->start,
			      flash_np->name);
	if (!mtd->name) {
		ret = -ENOMEM;
		goto err;
	}

	ret = nand_scan(mtd, fun->mchip_count);
	if (ret)
		goto err;

	ret = mtd_device_register(mtd, NULL, 0);
err:
	of_node_put(flash_np);
	if (ret)
		kfree(mtd->name);
	return ret;
}