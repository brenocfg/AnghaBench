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
 int /*<<< orphan*/  pr_info (char*,char*) ; 
 int tsc_async_resets ; 

void mark_tsc_async_resets(char *reason)
{
	if (tsc_async_resets)
		return;
	tsc_async_resets = true;
	pr_info("tsc: Marking TSC async resets true due to %s\n", reason);
}