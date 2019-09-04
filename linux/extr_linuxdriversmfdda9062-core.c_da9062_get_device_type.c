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
struct da9062 {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9062AA_DEVICE_ID ; 
 int DA9062AA_MRC_MASK ; 
 int DA9062AA_MRC_SHIFT ; 
 int /*<<< orphan*/  DA9062AA_VARIANT_ID ; 
 int DA9062AA_VRC_MASK ; 
 int DA9062AA_VRC_SHIFT ; 
 int DA9062_PMIC_DEVICE_ID ; 
 int DA9062_PMIC_VARIANT_MRC_AA ; 
#define  DA9062_PMIC_VARIANT_VRC_DA9061 129 
#define  DA9062_PMIC_VARIANT_VRC_DA9062 128 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,int,char*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int da9062_get_device_type(struct da9062 *chip)
{
	int device_id, variant_id, variant_mrc, variant_vrc;
	char *type;
	int ret;

	ret = regmap_read(chip->regmap, DA9062AA_DEVICE_ID, &device_id);
	if (ret < 0) {
		dev_err(chip->dev, "Cannot read chip ID.\n");
		return -EIO;
	}
	if (device_id != DA9062_PMIC_DEVICE_ID) {
		dev_err(chip->dev, "Invalid device ID: 0x%02x\n", device_id);
		return -ENODEV;
	}

	ret = regmap_read(chip->regmap, DA9062AA_VARIANT_ID, &variant_id);
	if (ret < 0) {
		dev_err(chip->dev, "Cannot read chip variant id.\n");
		return -EIO;
	}

	variant_vrc = (variant_id & DA9062AA_VRC_MASK) >> DA9062AA_VRC_SHIFT;

	switch (variant_vrc) {
	case DA9062_PMIC_VARIANT_VRC_DA9061:
		type = "DA9061";
		break;
	case DA9062_PMIC_VARIANT_VRC_DA9062:
		type = "DA9062";
		break;
	default:
		type = "Unknown";
		break;
	}

	dev_info(chip->dev,
		 "Device detected (device-ID: 0x%02X, var-ID: 0x%02X, %s)\n",
		 device_id, variant_id, type);

	variant_mrc = (variant_id & DA9062AA_MRC_MASK) >> DA9062AA_MRC_SHIFT;

	if (variant_mrc < DA9062_PMIC_VARIANT_MRC_AA) {
		dev_err(chip->dev,
			"Cannot support variant MRC: 0x%02X\n", variant_mrc);
		return -ENODEV;
	}

	return ret;
}