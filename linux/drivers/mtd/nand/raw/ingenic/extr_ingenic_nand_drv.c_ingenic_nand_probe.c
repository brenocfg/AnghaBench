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
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct ingenic_nfc {unsigned int num_banks; scalar_t__ ecc; int /*<<< orphan*/  chips; int /*<<< orphan*/  controller; struct device* dev; int /*<<< orphan*/  soc_info; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  cs ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  device_get_match_data (struct device*) ; 
 struct ingenic_nfc* devm_kzalloc (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ingenic_ecc_release (scalar_t__) ; 
 int ingenic_nand_init_chips (struct ingenic_nfc*,struct platform_device*) ; 
 unsigned int jz4780_nemc_num_banks (struct device*) ; 
 int /*<<< orphan*/  nand_controller_init (int /*<<< orphan*/ *) ; 
 scalar_t__ of_ingenic_ecc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ingenic_nfc*) ; 
 int /*<<< orphan*/  struct_size (struct ingenic_nfc*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int ingenic_nand_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	unsigned int num_banks;
	struct ingenic_nfc *nfc;
	int ret;

	num_banks = jz4780_nemc_num_banks(dev);
	if (num_banks == 0) {
		dev_err(dev, "no banks found\n");
		return -ENODEV;
	}

	nfc = devm_kzalloc(dev, struct_size(nfc, cs, num_banks), GFP_KERNEL);
	if (!nfc)
		return -ENOMEM;

	nfc->soc_info = device_get_match_data(dev);
	if (!nfc->soc_info)
		return -EINVAL;

	/*
	 * Check for ECC HW before we call nand_scan_ident, to prevent us from
	 * having to call it again if the ECC driver returns -EPROBE_DEFER.
	 */
	nfc->ecc = of_ingenic_ecc_get(dev->of_node);
	if (IS_ERR(nfc->ecc))
		return PTR_ERR(nfc->ecc);

	nfc->dev = dev;
	nfc->num_banks = num_banks;

	nand_controller_init(&nfc->controller);
	INIT_LIST_HEAD(&nfc->chips);

	ret = ingenic_nand_init_chips(nfc, pdev);
	if (ret) {
		if (nfc->ecc)
			ingenic_ecc_release(nfc->ecc);
		return ret;
	}

	platform_set_drvdata(pdev, nfc);
	return 0;
}