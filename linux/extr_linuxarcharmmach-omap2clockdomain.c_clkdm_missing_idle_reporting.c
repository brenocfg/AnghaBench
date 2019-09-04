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
struct clockdomain {int flags; } ;

/* Variables and functions */
 int CLKDM_MISSING_IDLE_REPORTING ; 

bool clkdm_missing_idle_reporting(struct clockdomain *clkdm)
{
	if (!clkdm)
		return false;

	return (clkdm->flags & CLKDM_MISSING_IDLE_REPORTING) ? true : false;
}