#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_5__ {void* read_oob; void* read_oob_raw; int /*<<< orphan*/  read_page; int /*<<< orphan*/  read_page_raw; int /*<<< orphan*/  read_subpage; void* write_oob; void* write_oob_raw; int /*<<< orphan*/  write_page; int /*<<< orphan*/  write_page_raw; int /*<<< orphan*/  write_subpage; int /*<<< orphan*/  mode; } ;
struct TYPE_4__ {int /*<<< orphan*/  cmd_ctrl; int /*<<< orphan*/  read_buf; int /*<<< orphan*/  read_byte; int /*<<< orphan*/  write_buf; int /*<<< orphan*/  write_byte; int /*<<< orphan*/  select_chip; int /*<<< orphan*/  dev_ready; } ;
struct nand_chip {int options; TYPE_2__ ecc; TYPE_1__ legacy; int /*<<< orphan*/ * controller; } ;
struct mtk_nfc_nand_chip {int nsels; int* sels; int /*<<< orphan*/  node; struct nand_chip nand; } ;
struct mtk_nfc {int /*<<< orphan*/  chips; int /*<<< orphan*/  controller; int /*<<< orphan*/  assigned_cs; } ;
struct TYPE_6__ {struct device* parent; } ;
struct mtd_info {int /*<<< orphan*/  name; TYPE_3__ dev; int /*<<< orphan*/  owner; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MTK_NAME ; 
 int MTK_NAND_MAX_NSELS ; 
 int /*<<< orphan*/  NAND_ECC_HW ; 
 int NAND_SUBPAGE_READ ; 
 int NAND_USE_BOUNCE_BUFFER ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct mtk_nfc_nand_chip* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mtd_device_register (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtd_set_ooblayout (struct mtd_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_nfc_cmd_ctrl ; 
 int /*<<< orphan*/  mtk_nfc_dev_ready ; 
 int /*<<< orphan*/  mtk_nfc_hw_init (struct mtk_nfc*) ; 
 int /*<<< orphan*/  mtk_nfc_ooblayout_ops ; 
 int /*<<< orphan*/  mtk_nfc_read_buf ; 
 int /*<<< orphan*/  mtk_nfc_read_byte ; 
 void* mtk_nfc_read_oob_std ; 
 int /*<<< orphan*/  mtk_nfc_read_page_hwecc ; 
 int /*<<< orphan*/  mtk_nfc_read_page_raw ; 
 int /*<<< orphan*/  mtk_nfc_read_subpage_hwecc ; 
 int /*<<< orphan*/  mtk_nfc_select_chip ; 
 int /*<<< orphan*/  mtk_nfc_write_buf ; 
 int /*<<< orphan*/  mtk_nfc_write_byte ; 
 void* mtk_nfc_write_oob_std ; 
 int /*<<< orphan*/  mtk_nfc_write_page_hwecc ; 
 int /*<<< orphan*/  mtk_nfc_write_page_raw ; 
 int /*<<< orphan*/  mtk_nfc_write_subpage_hwecc ; 
 int /*<<< orphan*/  nand_release (struct nand_chip*) ; 
 int nand_scan (struct nand_chip*,int) ; 
 int /*<<< orphan*/  nand_set_controller_data (struct nand_chip*,struct mtk_nfc*) ; 
 int /*<<< orphan*/  nand_set_flash_node (struct nand_chip*,struct device_node*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  of_get_property (struct device_node*,char*,int*) ; 
 int of_property_read_u32_index (struct device_node*,char*,int,int*) ; 
 scalar_t__ test_and_set_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mtk_nfc_nand_chip_init(struct device *dev, struct mtk_nfc *nfc,
				  struct device_node *np)
{
	struct mtk_nfc_nand_chip *chip;
	struct nand_chip *nand;
	struct mtd_info *mtd;
	int nsels;
	u32 tmp;
	int ret;
	int i;

	if (!of_get_property(np, "reg", &nsels))
		return -ENODEV;

	nsels /= sizeof(u32);
	if (!nsels || nsels > MTK_NAND_MAX_NSELS) {
		dev_err(dev, "invalid reg property size %d\n", nsels);
		return -EINVAL;
	}

	chip = devm_kzalloc(dev, sizeof(*chip) + nsels * sizeof(u8),
			    GFP_KERNEL);
	if (!chip)
		return -ENOMEM;

	chip->nsels = nsels;
	for (i = 0; i < nsels; i++) {
		ret = of_property_read_u32_index(np, "reg", i, &tmp);
		if (ret) {
			dev_err(dev, "reg property failure : %d\n", ret);
			return ret;
		}

		if (tmp >= MTK_NAND_MAX_NSELS) {
			dev_err(dev, "invalid CS: %u\n", tmp);
			return -EINVAL;
		}

		if (test_and_set_bit(tmp, &nfc->assigned_cs)) {
			dev_err(dev, "CS %u already assigned\n", tmp);
			return -EINVAL;
		}

		chip->sels[i] = tmp;
	}

	nand = &chip->nand;
	nand->controller = &nfc->controller;

	nand_set_flash_node(nand, np);
	nand_set_controller_data(nand, nfc);

	nand->options |= NAND_USE_BOUNCE_BUFFER | NAND_SUBPAGE_READ;
	nand->legacy.dev_ready = mtk_nfc_dev_ready;
	nand->legacy.select_chip = mtk_nfc_select_chip;
	nand->legacy.write_byte = mtk_nfc_write_byte;
	nand->legacy.write_buf = mtk_nfc_write_buf;
	nand->legacy.read_byte = mtk_nfc_read_byte;
	nand->legacy.read_buf = mtk_nfc_read_buf;
	nand->legacy.cmd_ctrl = mtk_nfc_cmd_ctrl;

	/* set default mode in case dt entry is missing */
	nand->ecc.mode = NAND_ECC_HW;

	nand->ecc.write_subpage = mtk_nfc_write_subpage_hwecc;
	nand->ecc.write_page_raw = mtk_nfc_write_page_raw;
	nand->ecc.write_page = mtk_nfc_write_page_hwecc;
	nand->ecc.write_oob_raw = mtk_nfc_write_oob_std;
	nand->ecc.write_oob = mtk_nfc_write_oob_std;

	nand->ecc.read_subpage = mtk_nfc_read_subpage_hwecc;
	nand->ecc.read_page_raw = mtk_nfc_read_page_raw;
	nand->ecc.read_page = mtk_nfc_read_page_hwecc;
	nand->ecc.read_oob_raw = mtk_nfc_read_oob_std;
	nand->ecc.read_oob = mtk_nfc_read_oob_std;

	mtd = nand_to_mtd(nand);
	mtd->owner = THIS_MODULE;
	mtd->dev.parent = dev;
	mtd->name = MTK_NAME;
	mtd_set_ooblayout(mtd, &mtk_nfc_ooblayout_ops);

	mtk_nfc_hw_init(nfc);

	ret = nand_scan(nand, nsels);
	if (ret)
		return ret;

	ret = mtd_device_register(mtd, NULL, 0);
	if (ret) {
		dev_err(dev, "mtd parse partition error\n");
		nand_release(nand);
		return ret;
	}

	list_add_tail(&chip->node, &nfc->chips);

	return 0;
}