#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int warn_thrshld; } ;
struct dasd_eckd_private {TYPE_1__ eps; } ;
struct dasd_device {struct dasd_eckd_private* private; } ;

/* Variables and functions */

__attribute__((used)) static int dasd_eckd_ext_pool_warn_thrshld(struct dasd_device *device)
{
	struct dasd_eckd_private *private = device->private;

	return private->eps.warn_thrshld;
}