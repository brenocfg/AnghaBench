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
struct cosm_device {int /*<<< orphan*/  dbg_dir; int /*<<< orphan*/  index; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  cosm_dbg ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct cosm_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  force_reset_fops ; 
 int /*<<< orphan*/  log_buf_fops ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

void cosm_create_debug_dir(struct cosm_device *cdev)
{
	char name[16];

	if (!cosm_dbg)
		return;

	scnprintf(name, sizeof(name), "mic%d", cdev->index);
	cdev->dbg_dir = debugfs_create_dir(name, cosm_dbg);

	debugfs_create_file("log_buf", 0444, cdev->dbg_dir, cdev,
			    &log_buf_fops);
	debugfs_create_file("force_reset", 0444, cdev->dbg_dir, cdev,
			    &force_reset_fops);
}