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
 int /*<<< orphan*/ * divas_proc_entry ; 
 int /*<<< orphan*/  divas_proc_name ; 
 int /*<<< orphan*/  proc_net_eicon ; 
 int /*<<< orphan*/  remove_proc_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void remove_divas_proc(void)
{
	if (divas_proc_entry) {
		remove_proc_entry(divas_proc_name, proc_net_eicon);
		divas_proc_entry = NULL;
	}
}