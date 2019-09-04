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
struct rdtgroup {int dummy; } ;
struct kernfs_open_file {int /*<<< orphan*/  kn; } ;

/* Variables and functions */
 int ENOENT ; 
 struct rdtgroup* rdtgroup_kn_lock_live (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdtgroup_kn_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_rdt_tasks (struct rdtgroup*,struct seq_file*) ; 

__attribute__((used)) static int rdtgroup_tasks_show(struct kernfs_open_file *of,
			       struct seq_file *s, void *v)
{
	struct rdtgroup *rdtgrp;
	int ret = 0;

	rdtgrp = rdtgroup_kn_lock_live(of->kn);
	if (rdtgrp)
		show_rdt_tasks(rdtgrp, s);
	else
		ret = -ENOENT;
	rdtgroup_kn_unlock(of->kn);

	return ret;
}