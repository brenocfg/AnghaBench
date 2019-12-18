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
typedef  int /*<<< orphan*/  u32 ;
struct tegra_nand_controller {struct nand_chip* chip; int /*<<< orphan*/  controller; } ;
struct nand_chip {int options; int /*<<< orphan*/ * controller; } ;
struct tegra_nand_chip {int /*<<< orphan*/  ecc; struct nand_chip chip; int /*<<< orphan*/  wp_gpio; int /*<<< orphan*/ * cs; } ;
struct TYPE_2__ {struct device* parent; } ;
struct mtd_info {char* name; int /*<<< orphan*/  owner; TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int NAND_NO_SUBPAGE_WRITE ; 
 int NAND_USE_BOUNCE_BUFFER ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct tegra_nand_chip* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int mtd_device_register (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtd_ooblayout_ecc (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nand_cleanup (struct nand_chip*) ; 
 int nand_scan (struct nand_chip*,int) ; 
 int /*<<< orphan*/  nand_set_flash_node (struct nand_chip*,struct device_node*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int of_get_child_count (struct device_node*) ; 
 struct device_node* of_get_next_child (struct device_node*,int /*<<< orphan*/ *) ; 
 int of_property_count_elems_of_size (struct device_node*,char*,int) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tegra_nand_chips_init(struct device *dev,
				 struct tegra_nand_controller *ctrl)
{
	struct device_node *np = dev->of_node;
	struct device_node *np_nand;
	int nsels, nchips = of_get_child_count(np);
	struct tegra_nand_chip *nand;
	struct mtd_info *mtd;
	struct nand_chip *chip;
	int ret;
	u32 cs;

	if (nchips != 1) {
		dev_err(dev, "Currently only one NAND chip supported\n");
		return -EINVAL;
	}

	np_nand = of_get_next_child(np, NULL);

	nsels = of_property_count_elems_of_size(np_nand, "reg", sizeof(u32));
	if (nsels != 1) {
		dev_err(dev, "Missing/invalid reg property\n");
		return -EINVAL;
	}

	/* Retrieve CS id, currently only single die NAND supported */
	ret = of_property_read_u32(np_nand, "reg", &cs);
	if (ret) {
		dev_err(dev, "could not retrieve reg property: %d\n", ret);
		return ret;
	}

	nand = devm_kzalloc(dev, sizeof(*nand), GFP_KERNEL);
	if (!nand)
		return -ENOMEM;

	nand->cs[0] = cs;

	nand->wp_gpio = devm_gpiod_get_optional(dev, "wp", GPIOD_OUT_LOW);

	if (IS_ERR(nand->wp_gpio)) {
		ret = PTR_ERR(nand->wp_gpio);
		dev_err(dev, "Failed to request WP GPIO: %d\n", ret);
		return ret;
	}

	chip = &nand->chip;
	chip->controller = &ctrl->controller;

	mtd = nand_to_mtd(chip);

	mtd->dev.parent = dev;
	mtd->owner = THIS_MODULE;

	nand_set_flash_node(chip, np_nand);

	if (!mtd->name)
		mtd->name = "tegra_nand";

	chip->options = NAND_NO_SUBPAGE_WRITE | NAND_USE_BOUNCE_BUFFER;

	ret = nand_scan(chip, 1);
	if (ret)
		return ret;

	mtd_ooblayout_ecc(mtd, 0, &nand->ecc);

	ret = mtd_device_register(mtd, NULL, 0);
	if (ret) {
		dev_err(dev, "Failed to register mtd device: %d\n", ret);
		nand_cleanup(chip);
		return ret;
	}

	ctrl->chip = chip;

	return 0;
}