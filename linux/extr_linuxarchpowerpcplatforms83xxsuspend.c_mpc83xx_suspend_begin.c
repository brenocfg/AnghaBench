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
typedef  int suspend_state_t ;

/* Variables and functions */
 int EINVAL ; 
#define  PM_SUSPEND_MEM 129 
#define  PM_SUSPEND_STANDBY 128 
 int deep_sleeping ; 
 int /*<<< orphan*/  has_deep_sleep ; 

__attribute__((used)) static int mpc83xx_suspend_begin(suspend_state_t state)
{
	switch (state) {
		case PM_SUSPEND_STANDBY:
			deep_sleeping = 0;
			return 0;

		case PM_SUSPEND_MEM:
			if (has_deep_sleep)
				deep_sleeping = 1;

			return 0;

		default:
			return -EINVAL;
	}
}