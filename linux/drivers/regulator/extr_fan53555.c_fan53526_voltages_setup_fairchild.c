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
struct fan53555_device_info {int chip_id; int vsel_min; int vsel_step; int /*<<< orphan*/  vsel_count; int /*<<< orphan*/  dev; int /*<<< orphan*/  chip_rev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  FAN53526_CHIP_ID_01 129 
#define  FAN53526_CHIP_REV_08 128 
 int /*<<< orphan*/  FAN53526_NVOLTAGES ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static int fan53526_voltages_setup_fairchild(struct fan53555_device_info *di)
{
	/* Init voltage range and step */
	switch (di->chip_id) {
	case FAN53526_CHIP_ID_01:
		switch (di->chip_rev) {
		case FAN53526_CHIP_REV_08:
			di->vsel_min = 600000;
			di->vsel_step = 6250;
			break;
		default:
			dev_err(di->dev,
				"Chip ID %d with rev %d not supported!\n",
				di->chip_id, di->chip_rev);
			return -EINVAL;
		}
		break;
	default:
		dev_err(di->dev,
			"Chip ID %d not supported!\n", di->chip_id);
		return -EINVAL;
	}

	di->vsel_count = FAN53526_NVOLTAGES;

	return 0;
}