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
struct sm501_devdata {scalar_t__ in_suspend; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdelay (unsigned int) ; 
 int /*<<< orphan*/  msleep (unsigned int) ; 

__attribute__((used)) static inline void sm501_mdelay(struct sm501_devdata *sm, unsigned int delay)
{
	/* during suspend/resume, we are currently not allowed to sleep,
	 * so change to using mdelay() instead of msleep() if we
	 * are in one of these paths */

	if (sm->in_suspend)
		mdelay(delay);
	else
		msleep(delay);
}