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
struct gb_svc {TYPE_1__* watchdog; } ;
struct TYPE_2__ {int enabled; } ;

/* Variables and functions */

bool gb_svc_watchdog_enabled(struct gb_svc *svc)
{
	if (!svc || !svc->watchdog)
		return false;
	return svc->watchdog->enabled;
}