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
struct rdtgroup {int dummy; } ;
struct kernfs_node {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct kernfs_node*) ; 
 int PTR_ERR (struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_activate (struct kernfs_node*) ; 
 struct kernfs_node* kernfs_create_dir (struct kernfs_node*,char*,int /*<<< orphan*/ ,struct rdtgroup*) ; 
 int /*<<< orphan*/  kernfs_get (struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_remove (struct kernfs_node*) ; 
 int rdtgroup_kn_set_ugid (struct kernfs_node*) ; 

__attribute__((used)) static int
mongroup_create_dir(struct kernfs_node *parent_kn, struct rdtgroup *prgrp,
		    char *name, struct kernfs_node **dest_kn)
{
	struct kernfs_node *kn;
	int ret;

	/* create the directory */
	kn = kernfs_create_dir(parent_kn, name, parent_kn->mode, prgrp);
	if (IS_ERR(kn))
		return PTR_ERR(kn);

	if (dest_kn)
		*dest_kn = kn;

	/*
	 * This extra ref will be put in kernfs_remove() and guarantees
	 * that @rdtgrp->kn is always accessible.
	 */
	kernfs_get(kn);

	ret = rdtgroup_kn_set_ugid(kn);
	if (ret)
		goto out_destroy;

	kernfs_activate(kn);

	return 0;

out_destroy:
	kernfs_remove(kn);
	return ret;
}