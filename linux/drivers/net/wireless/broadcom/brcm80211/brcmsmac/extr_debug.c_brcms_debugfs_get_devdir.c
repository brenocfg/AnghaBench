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
struct brcms_pub {struct dentry* dbgfs_dir; } ;

/* Variables and functions */

struct dentry *brcms_debugfs_get_devdir(struct brcms_pub *drvr)
{
	return drvr->dbgfs_dir;
}