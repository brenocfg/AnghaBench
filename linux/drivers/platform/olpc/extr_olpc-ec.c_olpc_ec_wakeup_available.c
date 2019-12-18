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
struct TYPE_2__ {int wakeup_available; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 TYPE_1__* ec_driver ; 

bool olpc_ec_wakeup_available(void)
{
	if (WARN_ON(!ec_driver))
		return false;

	return ec_driver->wakeup_available;
}