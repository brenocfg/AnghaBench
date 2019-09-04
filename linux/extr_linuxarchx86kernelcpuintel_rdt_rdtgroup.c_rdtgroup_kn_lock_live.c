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
struct rdtgroup {int flags; int /*<<< orphan*/  waitcount; } ;
struct kernfs_node {int dummy; } ;

/* Variables and functions */
 int RDT_DELETED ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kernfs_break_active_protection (struct kernfs_node*) ; 
 struct rdtgroup* kernfs_to_rdtgroup (struct kernfs_node*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdtgroup_mutex ; 

struct rdtgroup *rdtgroup_kn_lock_live(struct kernfs_node *kn)
{
	struct rdtgroup *rdtgrp = kernfs_to_rdtgroup(kn);

	if (!rdtgrp)
		return NULL;

	atomic_inc(&rdtgrp->waitcount);
	kernfs_break_active_protection(kn);

	mutex_lock(&rdtgroup_mutex);

	/* Was this group deleted while we waited? */
	if (rdtgrp->flags & RDT_DELETED)
		return NULL;

	return rdtgrp;
}