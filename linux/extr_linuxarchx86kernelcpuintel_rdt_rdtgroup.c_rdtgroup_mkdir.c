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
struct kernfs_node {int /*<<< orphan*/  parent; } ;
struct TYPE_2__ {struct kernfs_node* kn; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ is_mon_groups (struct kernfs_node*,char const*) ; 
 scalar_t__ rdt_alloc_capable ; 
 scalar_t__ rdt_mon_capable ; 
 TYPE_1__ rdtgroup_default ; 
 int rdtgroup_mkdir_ctrl_mon (struct kernfs_node*,struct kernfs_node*,char const*,int /*<<< orphan*/ ) ; 
 int rdtgroup_mkdir_mon (struct kernfs_node*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strchr (char const*,char) ; 

__attribute__((used)) static int rdtgroup_mkdir(struct kernfs_node *parent_kn, const char *name,
			  umode_t mode)
{
	/* Do not accept '\n' to avoid unparsable situation. */
	if (strchr(name, '\n'))
		return -EINVAL;

	/*
	 * If the parent directory is the root directory and RDT
	 * allocation is supported, add a control and monitoring
	 * subdirectory
	 */
	if (rdt_alloc_capable && parent_kn == rdtgroup_default.kn)
		return rdtgroup_mkdir_ctrl_mon(parent_kn, parent_kn, name, mode);

	/*
	 * If RDT monitoring is supported and the parent directory is a valid
	 * "mon_groups" directory, add a monitoring subdirectory.
	 */
	if (rdt_mon_capable && is_mon_groups(parent_kn, name))
		return rdtgroup_mkdir_mon(parent_kn, parent_kn->parent, name, mode);

	return -EPERM;
}