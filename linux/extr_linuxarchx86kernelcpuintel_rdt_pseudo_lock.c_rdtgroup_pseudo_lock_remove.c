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
struct rdtgroup {scalar_t__ mode; struct pseudo_lock_region* plr; int /*<<< orphan*/  closid; } ;
struct pseudo_lock_region {int /*<<< orphan*/  minor; int /*<<< orphan*/  debugfs_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RDT_MODE_PSEUDO_LOCKSETUP ; 
 int /*<<< orphan*/  closid_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pseudo_lock_class ; 
 int /*<<< orphan*/  pseudo_lock_cstates_relax (struct pseudo_lock_region*) ; 
 int /*<<< orphan*/  pseudo_lock_free (struct rdtgroup*) ; 
 int /*<<< orphan*/  pseudo_lock_major ; 
 int /*<<< orphan*/  pseudo_lock_minor_release (int /*<<< orphan*/ ) ; 

void rdtgroup_pseudo_lock_remove(struct rdtgroup *rdtgrp)
{
	struct pseudo_lock_region *plr = rdtgrp->plr;

	if (rdtgrp->mode == RDT_MODE_PSEUDO_LOCKSETUP) {
		/*
		 * Default group cannot be a pseudo-locked region so we can
		 * free closid here.
		 */
		closid_free(rdtgrp->closid);
		goto free;
	}

	pseudo_lock_cstates_relax(plr);
	debugfs_remove_recursive(rdtgrp->plr->debugfs_dir);
	device_destroy(pseudo_lock_class, MKDEV(pseudo_lock_major, plr->minor));
	pseudo_lock_minor_release(plr->minor);

free:
	pseudo_lock_free(rdtgrp);
}