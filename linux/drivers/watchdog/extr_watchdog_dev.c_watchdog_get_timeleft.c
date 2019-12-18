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
struct watchdog_device {TYPE_1__* ops; } ;
struct TYPE_2__ {unsigned int (* get_timeleft ) (struct watchdog_device*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 unsigned int stub1 (struct watchdog_device*) ; 

__attribute__((used)) static int watchdog_get_timeleft(struct watchdog_device *wdd,
							unsigned int *timeleft)
{
	*timeleft = 0;

	if (!wdd->ops->get_timeleft)
		return -EOPNOTSUPP;

	*timeleft = wdd->ops->get_timeleft(wdd);

	return 0;
}