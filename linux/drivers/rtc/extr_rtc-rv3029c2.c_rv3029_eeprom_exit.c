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
 int /*<<< orphan*/  RV3029_ONOFF_CTRL ; 
 int /*<<< orphan*/  RV3029_ONOFF_CTRL_EERE ; 
 int rv3029_update_bits (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rv3029_eeprom_exit(struct device *dev)
{
	/* Re-enable eeprom refresh */
	return rv3029_update_bits(dev, RV3029_ONOFF_CTRL,
				  RV3029_ONOFF_CTRL_EERE,
				  RV3029_ONOFF_CTRL_EERE);
}