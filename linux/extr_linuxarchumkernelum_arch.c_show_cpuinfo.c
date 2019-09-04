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
struct seq_file {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  host_info ; 
 int loops_per_jiffy ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static int show_cpuinfo(struct seq_file *m, void *v)
{
	int index = 0;

	seq_printf(m, "processor\t: %d\n", index);
	seq_printf(m, "vendor_id\t: User Mode Linux\n");
	seq_printf(m, "model name\t: UML\n");
	seq_printf(m, "mode\t\t: skas\n");
	seq_printf(m, "host\t\t: %s\n", host_info);
	seq_printf(m, "bogomips\t: %lu.%02lu\n\n",
		   loops_per_jiffy/(500000/HZ),
		   (loops_per_jiffy/(5000/HZ)) % 100);

	return 0;
}