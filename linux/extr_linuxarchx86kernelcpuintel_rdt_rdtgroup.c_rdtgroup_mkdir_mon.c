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
typedef  int /*<<< orphan*/  umode_t ;
struct TYPE_2__ {int /*<<< orphan*/  crdtgrp_list; struct rdtgroup* parent; } ;
struct rdtgroup {TYPE_1__ mon; int /*<<< orphan*/  closid; } ;
struct kernfs_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDTMON_GROUP ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mkdir_rdt_prepare (struct kernfs_node*,struct kernfs_node*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rdtgroup**) ; 
 int /*<<< orphan*/  rdtgroup_kn_unlock (struct kernfs_node*) ; 

__attribute__((used)) static int rdtgroup_mkdir_mon(struct kernfs_node *parent_kn,
			      struct kernfs_node *prgrp_kn,
			      const char *name,
			      umode_t mode)
{
	struct rdtgroup *rdtgrp, *prgrp;
	int ret;

	ret = mkdir_rdt_prepare(parent_kn, prgrp_kn, name, mode, RDTMON_GROUP,
				&rdtgrp);
	if (ret)
		return ret;

	prgrp = rdtgrp->mon.parent;
	rdtgrp->closid = prgrp->closid;

	/*
	 * Add the rdtgrp to the list of rdtgrps the parent
	 * ctrl_mon group has to track.
	 */
	list_add_tail(&rdtgrp->mon.crdtgrp_list, &prgrp->mon.crdtgrp_list);

	rdtgroup_kn_unlock(prgrp_kn);
	return ret;
}