#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int NR_PORTS ; 
 TYPE_1__* rs_table ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static int rs_proc_show(struct seq_file *m, void *v)
{
	int i;

	seq_printf(m, "simserinfo:1.0\n");
	for (i = 0; i < NR_PORTS; i++)
		seq_printf(m, "%d: uart:16550 port:3F8 irq:%d\n",
		       i, rs_table[i].irq);
	return 0;
}