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
struct seq_file {struct ptdump_info* private; } ;
struct ptdump_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ptdump_walk_pgd (struct seq_file*,struct ptdump_info*) ; 

__attribute__((used)) static int ptdump_show(struct seq_file *m, void *v)
{
	struct ptdump_info *info = m->private;
	ptdump_walk_pgd(m, info);
	return 0;
}