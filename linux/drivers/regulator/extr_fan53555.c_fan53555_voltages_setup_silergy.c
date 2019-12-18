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
struct fan53555_device_info {int chip_id; int vsel_min; int vsel_step; int /*<<< orphan*/  vsel_count; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FAN53555_NVOLTAGES ; 
#define  SILERGY_SYR82X 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int fan53555_voltages_setup_silergy(struct fan53555_device_info *di)
{
	/* Init voltage range and step */
	switch (di->chip_id) {
	case SILERGY_SYR82X:
		di->vsel_min = 712500;
		di->vsel_step = 12500;
		break;
	default:
		dev_err(di->dev,
			"Chip ID %d not supported!\n", di->chip_id);
		return -EINVAL;
	}

	di->vsel_count = FAN53555_NVOLTAGES;

	return 0;
}