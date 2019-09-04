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
struct kernfs_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLOBAL_ROOT_GID ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 scalar_t__ IS_ERR (struct kernfs_node*) ; 
 int PTR_ERR (struct kernfs_node*) ; 
 struct kernfs_node* __kernfs_create_file (struct kernfs_node*,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kernfs_remove (struct kernfs_node*) ; 
 int /*<<< orphan*/  kf_mondata_ops ; 
 int rdtgroup_kn_set_ugid (struct kernfs_node*) ; 

__attribute__((used)) static int mon_addfile(struct kernfs_node *parent_kn, const char *name,
		       void *priv)
{
	struct kernfs_node *kn;
	int ret = 0;

	kn = __kernfs_create_file(parent_kn, name, 0444,
				  GLOBAL_ROOT_UID, GLOBAL_ROOT_GID, 0,
				  &kf_mondata_ops, priv, NULL, NULL);
	if (IS_ERR(kn))
		return PTR_ERR(kn);

	ret = rdtgroup_kn_set_ugid(kn);
	if (ret) {
		kernfs_remove(kn);
		return ret;
	}

	return ret;
}