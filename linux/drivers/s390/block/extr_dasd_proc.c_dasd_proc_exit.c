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
 int /*<<< orphan*/ * dasd_proc_root_entry ; 
 int /*<<< orphan*/  remove_proc_entry (char*,int /*<<< orphan*/ *) ; 

void
dasd_proc_exit(void)
{
	remove_proc_entry("devices", dasd_proc_root_entry);
	remove_proc_entry("statistics", dasd_proc_root_entry);
	remove_proc_entry("dasd", NULL);
}