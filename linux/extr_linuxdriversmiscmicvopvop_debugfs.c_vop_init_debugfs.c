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
struct vop_info {int /*<<< orphan*/  dbg; TYPE_1__* vpdev; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_2__ {int /*<<< orphan*/  dnode; } ;

/* Variables and functions */
 char* KBUILD_MODNAME ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct vop_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dp_ops ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_info_ops ; 

void vop_init_debugfs(struct vop_info *vi)
{
	char name[16];

	snprintf(name, sizeof(name), "%s%d", KBUILD_MODNAME, vi->vpdev->dnode);
	vi->dbg = debugfs_create_dir(name, NULL);
	if (!vi->dbg) {
		pr_err("can't create debugfs dir vop\n");
		return;
	}
	debugfs_create_file("dp", 0444, vi->dbg, vi, &dp_ops);
	debugfs_create_file("vdev_info", 0444, vi->dbg, vi, &vdev_info_ops);
}