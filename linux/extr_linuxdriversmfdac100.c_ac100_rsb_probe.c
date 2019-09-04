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
struct sunxi_rsb_device {int /*<<< orphan*/  dev; } ;
struct ac100_dev {int /*<<< orphan*/ * dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLATFORM_DEVID_NONE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ac100_cells ; 
 int /*<<< orphan*/  ac100_regmap_config ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct ac100_dev* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_mfd_add_devices (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_regmap_init_sunxi_rsb (struct sunxi_rsb_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sunxi_rsb_device_set_drvdata (struct sunxi_rsb_device*,struct ac100_dev*) ; 

__attribute__((used)) static int ac100_rsb_probe(struct sunxi_rsb_device *rdev)
{
	struct ac100_dev *ac100;
	int ret;

	ac100 = devm_kzalloc(&rdev->dev, sizeof(*ac100), GFP_KERNEL);
	if (!ac100)
		return -ENOMEM;

	ac100->dev = &rdev->dev;
	sunxi_rsb_device_set_drvdata(rdev, ac100);

	ac100->regmap = devm_regmap_init_sunxi_rsb(rdev, &ac100_regmap_config);
	if (IS_ERR(ac100->regmap)) {
		ret = PTR_ERR(ac100->regmap);
		dev_err(ac100->dev, "regmap init failed: %d\n", ret);
		return ret;
	}

	ret = devm_mfd_add_devices(ac100->dev, PLATFORM_DEVID_NONE, ac100_cells,
				   ARRAY_SIZE(ac100_cells), NULL, 0, NULL);
	if (ret) {
		dev_err(ac100->dev, "failed to add MFD devices: %d\n", ret);
		return ret;
	}

	return 0;
}