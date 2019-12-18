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
 int /*<<< orphan*/  mic_msi_irq_info_fops ; 
 int /*<<< orphan*/  mic_post_code_fops ; 
 int /*<<< orphan*/  mic_smpt_fops ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

void mic_create_debug_dir(struct mic_device *mdev)
{
	char name[16];

	if (!mic_dbg)
		return;

	scnprintf(name, sizeof(name), "mic%d", mdev->id);
	mdev->dbg_dir = debugfs_create_dir(name, mic_dbg);

	debugfs_create_file("smpt", 0444, mdev->dbg_dir, mdev,
			    &mic_smpt_fops);

	debugfs_create_file("post_code", 0444, mdev->dbg_dir, mdev,
			    &mic_post_code_fops);

	debugfs_create_file("msi_irq_info", 0444, mdev->dbg_dir, mdev,
			    &mic_msi_irq_info_fops);
}