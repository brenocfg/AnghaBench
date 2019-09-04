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
 int /*<<< orphan*/  CPUHP_AP_ARM_SDEI_STARTING ; 
 int /*<<< orphan*/  cpuhp_remove_state (int /*<<< orphan*/ ) ; 
 int sdei_unregister_shared () ; 

__attribute__((used)) static int sdei_device_freeze(struct device *dev)
{
	int err;

	/* unregister private events */
	cpuhp_remove_state(CPUHP_AP_ARM_SDEI_STARTING);

	err = sdei_unregister_shared();
	if (err)
		return err;

	return 0;
}