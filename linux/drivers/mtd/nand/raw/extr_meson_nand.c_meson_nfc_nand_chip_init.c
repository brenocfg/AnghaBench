#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nand_chip {int /*<<< orphan*/  options; TYPE_1__* controller; } ;
struct TYPE_4__ {struct device* parent; } ;
struct mtd_info {TYPE_2__ dev; int /*<<< orphan*/  owner; } ;
struct meson_nfc_nand_chip {int nsels; int /*<<< orphan*/  node; struct nand_chip nand; } ;
struct TYPE_3__ {int /*<<< orphan*/ * ops; } ;
struct meson_nfc {int /*<<< orphan*/  chips; TYPE_1__ controller; int /*<<< orphan*/  assigned_cs; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_CE_NUM ; 
 int /*<<< orphan*/  NAND_USE_BOUNCE_BUFFER ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct meson_nfc_nand_chip* devm_kzalloc (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  meson_nand_controller_ops ; 
 int mtd_device_register (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_cleanup (struct nand_chip*) ; 
 int nand_scan (struct nand_chip*,int) ; 
 int /*<<< orphan*/  nand_set_controller_data (struct nand_chip*,struct meson_nfc*) ; 
 int /*<<< orphan*/  nand_set_flash_node (struct nand_chip*,struct device_node*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int of_property_count_elems_of_size (struct device_node*,char*,int) ; 
 int of_property_read_u32_index (struct device_node*,char*,int,int*) ; 
 int /*<<< orphan*/  sels ; 
 int /*<<< orphan*/  struct_size (struct meson_nfc_nand_chip*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_and_set_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
meson_nfc_nand_chip_init(struct device *dev,
			 struct meson_nfc *nfc, struct device_node *np)
{
	struct meson_nfc_nand_chip *meson_chip;
	struct nand_chip *nand;
	struct mtd_info *mtd;
	int ret, i;
	u32 tmp, nsels;

	nsels = of_property_count_elems_of_size(np, "reg", sizeof(u32));
	if (!nsels || nsels > MAX_CE_NUM) {
		dev_err(dev, "invalid register property size\n");
		return -EINVAL;
	}

	meson_chip = devm_kzalloc(dev, struct_size(meson_chip, sels, nsels),
				  GFP_KERNEL);
	if (!meson_chip)
		return -ENOMEM;

	meson_chip->nsels = nsels;

	for (i = 0; i < nsels; i++) {
		ret = of_property_read_u32_index(np, "reg", i, &tmp);
		if (ret) {
			dev_err(dev, "could not retrieve register property: %d\n",
				ret);
			return ret;
		}

		if (test_and_set_bit(tmp, &nfc->assigned_cs)) {
			dev_err(dev, "CS %d already assigned\n", tmp);
			return -EINVAL;
		}
	}

	nand = &meson_chip->nand;
	nand->controller = &nfc->controller;
	nand->controller->ops = &meson_nand_controller_ops;
	nand_set_flash_node(nand, np);
	nand_set_controller_data(nand, nfc);

	nand->options |= NAND_USE_BOUNCE_BUFFER;
	mtd = nand_to_mtd(nand);
	mtd->owner = THIS_MODULE;
	mtd->dev.parent = dev;

	ret = nand_scan(nand, nsels);
	if (ret)
		return ret;

	ret = mtd_device_register(mtd, NULL, 0);
	if (ret) {
		dev_err(dev, "failed to register MTD device: %d\n", ret);
		nand_cleanup(nand);
		return ret;
	}

	list_add_tail(&meson_chip->node, &nfc->chips);

	return 0;
}