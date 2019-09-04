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

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  dump_fit_entry (struct seq_file*,unsigned long*) ; 
 scalar_t__ get_fit_entry (unsigned long,int,unsigned long*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int proc_fit_show(struct seq_file *m, void *v)
{
	unsigned long nasid = (unsigned long)m->private;
	unsigned long fentry[2];
	int index;

	for (index=0;;index++) {
		BUG_ON(index * 60 > PAGE_SIZE);
		if (get_fit_entry(nasid, index, fentry, NULL, 0))
			break;
		dump_fit_entry(m, fentry);
	}
	return 0;
}