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
 int /*<<< orphan*/  debugfs_remove_recursive (struct dentry*) ; 

void nfp_net_debugfs_dir_clean(struct dentry **dir)
{
	debugfs_remove_recursive(*dir);
	*dir = NULL;
}