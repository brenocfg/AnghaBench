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
struct thermal_zone_device {int /*<<< orphan*/  device; struct kirkwood_thermal_priv* devdata; } ;
struct kirkwood_thermal_priv {int /*<<< orphan*/  sensor; } ;

/* Variables and functions */
 int EIO ; 
 unsigned long KIRKWOOD_THERMAL_TEMP_MASK ; 
 unsigned long KIRKWOOD_THERMAL_TEMP_OFFSET ; 
 unsigned long KIRKWOOD_THERMAL_VALID_MASK ; 
 unsigned long KIRKWOOD_THERMAL_VALID_OFFSET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 unsigned long readl_relaxed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kirkwood_get_temp(struct thermal_zone_device *thermal,
			  int *temp)
{
	unsigned long reg;
	struct kirkwood_thermal_priv *priv = thermal->devdata;

	reg = readl_relaxed(priv->sensor);

	/* Valid check */
	if (!((reg >> KIRKWOOD_THERMAL_VALID_OFFSET) &
	    KIRKWOOD_THERMAL_VALID_MASK)) {
		dev_err(&thermal->device,
			"Temperature sensor reading not valid\n");
		return -EIO;
	}

	/*
	 * Calculate temperature. According to Marvell internal
	 * documentation the formula for this is:
	 * Celsius = (322-reg)/1.3625
	 */
	reg = (reg >> KIRKWOOD_THERMAL_TEMP_OFFSET) &
		KIRKWOOD_THERMAL_TEMP_MASK;
	*temp = ((3220000000UL - (10000000UL * reg)) / 13625);

	return 0;
}