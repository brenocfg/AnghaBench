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
struct ad5820_device {int standby; int /*<<< orphan*/  vana; } ;

/* Variables and functions */
 int ad5820_update_hw (struct ad5820_device*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad5820_power_on(struct ad5820_device *coil, bool restore)
{
	int ret;

	ret = regulator_enable(coil->vana);
	if (ret < 0)
		return ret;

	if (restore) {
		/* Restore the hardware settings. */
		coil->standby = false;
		ret = ad5820_update_hw(coil);
		if (ret)
			goto fail;
	}
	return 0;

fail:
	coil->standby = true;
	regulator_disable(coil->vana);

	return ret;
}