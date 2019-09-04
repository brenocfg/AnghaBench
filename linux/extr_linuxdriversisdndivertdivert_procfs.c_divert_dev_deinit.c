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

int
divert_dev_deinit(void)
{

#ifdef CONFIG_PROC_FS
	remove_proc_entry("divert", isdn_proc_entry);
	remove_proc_entry("isdn", init_net.proc_net);
#endif	/* CONFIG_PROC_FS */

	return (0);
}