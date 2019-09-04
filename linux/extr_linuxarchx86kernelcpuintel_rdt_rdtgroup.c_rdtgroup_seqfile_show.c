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
struct seq_file {struct kernfs_open_file* private; } ;
struct rftype {int (* seq_show ) (struct kernfs_open_file*,struct seq_file*,void*) ;} ;
struct kernfs_open_file {TYPE_1__* kn; } ;
struct TYPE_2__ {struct rftype* priv; } ;

/* Variables and functions */
 int stub1 (struct kernfs_open_file*,struct seq_file*,void*) ; 

__attribute__((used)) static int rdtgroup_seqfile_show(struct seq_file *m, void *arg)
{
	struct kernfs_open_file *of = m->private;
	struct rftype *rft = of->kn->priv;

	if (rft->seq_show)
		return rft->seq_show(of, m, arg);
	return 0;
}