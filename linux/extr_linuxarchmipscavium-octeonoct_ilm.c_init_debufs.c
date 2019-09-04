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
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 struct dentry* debugfs_create_file (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dir ; 
 int /*<<< orphan*/  oct_ilm_ops ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  reset_statistics_ops ; 

__attribute__((used)) static int init_debufs(void)
{
	struct dentry *show_dentry;
	dir = debugfs_create_dir("oct_ilm", 0);
	if (!dir) {
		pr_err("oct_ilm: failed to create debugfs entry oct_ilm\n");
		return -1;
	}

	show_dentry = debugfs_create_file("statistics", 0222, dir, NULL,
					  &oct_ilm_ops);
	if (!show_dentry) {
		pr_err("oct_ilm: failed to create debugfs entry oct_ilm/statistics\n");
		return -1;
	}

	show_dentry = debugfs_create_file("reset", 0222, dir, NULL,
					  &reset_statistics_ops);
	if (!show_dentry) {
		pr_err("oct_ilm: failed to create debugfs entry oct_ilm/reset\n");
		return -1;
	}

	return 0;

}