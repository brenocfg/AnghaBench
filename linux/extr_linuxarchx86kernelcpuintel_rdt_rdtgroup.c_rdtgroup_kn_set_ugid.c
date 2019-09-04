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
struct iattr {int ia_valid; int /*<<< orphan*/  ia_gid; int /*<<< orphan*/  ia_uid; } ;

/* Variables and functions */
 int ATTR_GID ; 
 int ATTR_UID ; 
 int /*<<< orphan*/  GLOBAL_ROOT_GID ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 int /*<<< orphan*/  current_fsgid () ; 
 int /*<<< orphan*/  current_fsuid () ; 
 scalar_t__ gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kernfs_setattr (struct kernfs_node*,struct iattr*) ; 
 scalar_t__ uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rdtgroup_kn_set_ugid(struct kernfs_node *kn)
{
	struct iattr iattr = { .ia_valid = ATTR_UID | ATTR_GID,
				.ia_uid = current_fsuid(),
				.ia_gid = current_fsgid(), };

	if (uid_eq(iattr.ia_uid, GLOBAL_ROOT_UID) &&
	    gid_eq(iattr.ia_gid, GLOBAL_ROOT_GID))
		return 0;

	return kernfs_setattr(kn, &iattr);
}