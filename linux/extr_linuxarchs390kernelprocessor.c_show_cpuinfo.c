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
 int /*<<< orphan*/  machine_has_cpu_mhz ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,unsigned long) ; 
 int /*<<< orphan*/  show_cpu_mhz (struct seq_file*,unsigned long) ; 
 int /*<<< orphan*/  show_cpu_summary (struct seq_file*,void*) ; 

__attribute__((used)) static int show_cpuinfo(struct seq_file *m, void *v)
{
	unsigned long n = (unsigned long) v - 1;

	if (!n)
		show_cpu_summary(m, v);
	if (!machine_has_cpu_mhz)
		return 0;
	seq_printf(m, "\ncpu number      : %ld\n", n);
	show_cpu_mhz(m, n);
	return 0;
}