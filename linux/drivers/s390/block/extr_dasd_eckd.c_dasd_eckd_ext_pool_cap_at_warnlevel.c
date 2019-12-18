#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int capacity_at_warnlevel; } ;
struct TYPE_4__ {TYPE_1__ flags; } ;
struct dasd_eckd_private {TYPE_2__ eps; } ;
struct dasd_device {struct dasd_eckd_private* private; } ;

/* Variables and functions */

__attribute__((used)) static int dasd_eckd_ext_pool_cap_at_warnlevel(struct dasd_device *device)
{
	struct dasd_eckd_private *private = device->private;

	return private->eps.flags.capacity_at_warnlevel;
}