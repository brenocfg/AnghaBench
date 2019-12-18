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
struct cros_ec_device {scalar_t__ ec; scalar_t__ pd; } ;

/* Variables and functions */
 int /*<<< orphan*/  platform_device_unregister (scalar_t__) ; 

int cros_ec_unregister(struct cros_ec_device *ec_dev)
{
	if (ec_dev->pd)
		platform_device_unregister(ec_dev->pd);
	platform_device_unregister(ec_dev->ec);

	return 0;
}