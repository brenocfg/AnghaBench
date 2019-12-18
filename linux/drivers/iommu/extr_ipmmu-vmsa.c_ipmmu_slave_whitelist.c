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
struct device {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/ * rcar_gen3_slave_whitelist ; 
 int /*<<< orphan*/  soc_device_match (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soc_rcar_gen3 ; 
 int /*<<< orphan*/  soc_rcar_gen3_whitelist ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ipmmu_slave_whitelist(struct device *dev)
{
	unsigned int i;

	/*
	 * For R-Car Gen3 use a white list to opt-in slave devices.
	 * For Other SoCs, this returns true anyway.
	 */
	if (!soc_device_match(soc_rcar_gen3))
		return true;

	/* Check whether this R-Car Gen3 can use the IPMMU correctly or not */
	if (!soc_device_match(soc_rcar_gen3_whitelist))
		return false;

	/* Check whether this slave device can work with the IPMMU */
	for (i = 0; i < ARRAY_SIZE(rcar_gen3_slave_whitelist); i++) {
		if (!strcmp(dev_name(dev), rcar_gen3_slave_whitelist[i]))
			return true;
	}

	/* Otherwise, do not allow use of IPMMU */
	return false;
}