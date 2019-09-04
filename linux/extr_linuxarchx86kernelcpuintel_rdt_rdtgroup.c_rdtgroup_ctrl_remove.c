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
struct rdtgroup {int /*<<< orphan*/  kn; int /*<<< orphan*/  rdtgroup_list; int /*<<< orphan*/  flags; } ;
struct kernfs_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDT_DELETED ; 
 int /*<<< orphan*/  kernfs_get (struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rdtgroup_ctrl_remove(struct kernfs_node *kn,
				struct rdtgroup *rdtgrp)
{
	rdtgrp->flags = RDT_DELETED;
	list_del(&rdtgrp->rdtgroup_list);

	/*
	 * one extra hold on this, will drop when we kfree(rdtgrp)
	 * in rdtgroup_kn_unlock()
	 */
	kernfs_get(kn);
	kernfs_remove(rdtgrp->kn);
	return 0;
}