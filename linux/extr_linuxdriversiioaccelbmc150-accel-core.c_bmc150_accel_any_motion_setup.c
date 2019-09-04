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
struct bmc150_accel_trigger {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int bmc150_accel_update_slope (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bmc150_accel_any_motion_setup(struct bmc150_accel_trigger *t,
					 bool state)
{
	if (state)
		return bmc150_accel_update_slope(t->data);

	return 0;
}