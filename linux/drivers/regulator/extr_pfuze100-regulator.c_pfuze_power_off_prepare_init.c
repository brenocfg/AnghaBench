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
struct pfuze_chip {scalar_t__ chip_id; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 scalar_t__ PFUZE100 ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pfuze_power_off_prepare ; 
 scalar_t__ pm_power_off_prepare ; 
 struct pfuze_chip* syspm_pfuze_chip ; 

__attribute__((used)) static int pfuze_power_off_prepare_init(struct pfuze_chip *pfuze_chip)
{
	if (pfuze_chip->chip_id != PFUZE100) {
		dev_warn(pfuze_chip->dev, "Requested pm_power_off_prepare handler for not supported chip\n");
		return -ENODEV;
	}

	if (pm_power_off_prepare) {
		dev_warn(pfuze_chip->dev, "pm_power_off_prepare is already registered.\n");
		return -EBUSY;
	}

	if (syspm_pfuze_chip) {
		dev_warn(pfuze_chip->dev, "syspm_pfuze_chip is already set.\n");
		return -EBUSY;
	}

	syspm_pfuze_chip = pfuze_chip;
	pm_power_off_prepare = pfuze_power_off_prepare;

	return 0;
}