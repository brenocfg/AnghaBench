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

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ console_suspend_enabled ; 

__attribute__((used)) static int rmobile_pd_suspend_console(void)
{
	/*
	 * Serial consoles make use of SCIF hardware located in this domain,
	 * hence keep the power domain on if "no_console_suspend" is set.
	 */
	return console_suspend_enabled ? 0 : -EBUSY;
}