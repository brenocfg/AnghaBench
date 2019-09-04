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
struct seq_file {scalar_t__ private; } ;
typedef  int /*<<< orphan*/  banner ;

/* Variables and functions */
 scalar_t__ FIT_ENTRY_SAL_A ; 
 int /*<<< orphan*/  FIT_MAJOR (unsigned long) ; 
 int /*<<< orphan*/  FIT_MINOR (unsigned long) ; 
 scalar_t__ FIT_TYPE (unsigned long) ; 
 scalar_t__ get_fit_entry (unsigned long,int,unsigned long*,char*,int) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,...) ; 

__attribute__((used)) static int proc_version_show(struct seq_file *m, void *v)
{
	unsigned long nasid = (unsigned long)m->private;
	unsigned long fentry[2];
	char banner[128];
	int index;

	for (index = 0; ; index++) {
		if (get_fit_entry(nasid, index, fentry, banner,
				  sizeof(banner)))
			return 0;
		if (FIT_TYPE(fentry[1]) == FIT_ENTRY_SAL_A)
			break;
	}

	seq_printf(m, "%x.%02x\n", FIT_MAJOR(fentry[1]), FIT_MINOR(fentry[1]));

	if (banner[0])
		seq_printf(m, "%s\n", banner);
	return 0;
}