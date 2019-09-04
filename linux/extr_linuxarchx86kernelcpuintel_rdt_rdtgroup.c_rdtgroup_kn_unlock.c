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
struct rdtgroup {int flags; scalar_t__ mode; int /*<<< orphan*/  kn; int /*<<< orphan*/  waitcount; } ;
struct kernfs_node {int dummy; } ;

/* Variables and functions */
 int RDT_DELETED ; 
 scalar_t__ RDT_MODE_PSEUDO_LOCKED ; 
 scalar_t__ RDT_MODE_PSEUDO_LOCKSETUP ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kernfs_put (int /*<<< orphan*/ ) ; 
 struct rdtgroup* kernfs_to_rdtgroup (struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_unbreak_active_protection (struct kernfs_node*) ; 
 int /*<<< orphan*/  kfree (struct rdtgroup*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdtgroup_mutex ; 
 int /*<<< orphan*/  rdtgroup_pseudo_lock_remove (struct rdtgroup*) ; 

void rdtgroup_kn_unlock(struct kernfs_node *kn)
{
	struct rdtgroup *rdtgrp = kernfs_to_rdtgroup(kn);

	if (!rdtgrp)
		return;

	mutex_unlock(&rdtgroup_mutex);

	if (atomic_dec_and_test(&rdtgrp->waitcount) &&
	    (rdtgrp->flags & RDT_DELETED)) {
		if (rdtgrp->mode == RDT_MODE_PSEUDO_LOCKSETUP ||
		    rdtgrp->mode == RDT_MODE_PSEUDO_LOCKED)
			rdtgroup_pseudo_lock_remove(rdtgrp);
		kernfs_unbreak_active_protection(kn);
		kernfs_put(rdtgrp->kn);
		kfree(rdtgrp);
	} else {
		kernfs_unbreak_active_protection(kn);
	}
}