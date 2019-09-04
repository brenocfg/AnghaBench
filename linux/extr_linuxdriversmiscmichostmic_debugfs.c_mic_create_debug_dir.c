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
struct mic_device {int /*<<< orphan*/  dbg_dir; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct mic_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mic_dbg ; 
 int /*<<< orphan*/  msi_irq_info_ops ; 
 int /*<<< orphan*/  post_code_ops ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smpt_file_ops ; 

void mic_create_debug_dir(struct mic_device *mdev)
{
	char name[16];

	if (!mic_dbg)
		return;

	scnprintf(name, sizeof(name), "mic%d", mdev->id);
	mdev->dbg_dir = debugfs_create_dir(name, mic_dbg);
	if (!mdev->dbg_dir)
		return;

	debugfs_create_file("smpt", 0444, mdev->dbg_dir, mdev, &smpt_file_ops);

	debugfs_create_file("post_code", 0444, mdev->dbg_dir, mdev,
			    &post_code_ops);

	debugfs_create_file("msi_irq_info", 0444, mdev->dbg_dir, mdev,
			    &msi_irq_info_ops);
}