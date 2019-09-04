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
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rd_queue ; 

int
divert_dev_init(void)
{

	init_waitqueue_head(&rd_queue);

#ifdef CONFIG_PROC_FS
	isdn_proc_entry = proc_mkdir("isdn", init_net.proc_net);
	if (!isdn_proc_entry)
		return (-1);
	isdn_divert_entry = proc_create("divert", S_IFREG | S_IRUGO,
					isdn_proc_entry, &isdn_fops);
	if (!isdn_divert_entry) {
		remove_proc_entry("isdn", init_net.proc_net);
		return (-1);
	}
#endif	/* CONFIG_PROC_FS */

	return (0);
}