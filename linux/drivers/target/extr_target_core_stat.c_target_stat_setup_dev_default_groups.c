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
struct TYPE_2__ {int /*<<< orphan*/  stat_group; int /*<<< orphan*/  scsi_lu_group; int /*<<< orphan*/  scsi_tgt_dev_group; int /*<<< orphan*/  scsi_dev_group; } ;
struct se_device {TYPE_1__ dev_stat_grps; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_group_init_type_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  configfs_add_default_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  target_stat_scsi_dev_cit ; 
 int /*<<< orphan*/  target_stat_scsi_lu_cit ; 
 int /*<<< orphan*/  target_stat_scsi_tgt_dev_cit ; 

void target_stat_setup_dev_default_groups(struct se_device *dev)
{
	config_group_init_type_name(&dev->dev_stat_grps.scsi_dev_group,
			"scsi_dev", &target_stat_scsi_dev_cit);
	configfs_add_default_group(&dev->dev_stat_grps.scsi_dev_group,
			&dev->dev_stat_grps.stat_group);

	config_group_init_type_name(&dev->dev_stat_grps.scsi_tgt_dev_group,
			"scsi_tgt_dev", &target_stat_scsi_tgt_dev_cit);
	configfs_add_default_group(&dev->dev_stat_grps.scsi_tgt_dev_group,
			&dev->dev_stat_grps.stat_group);

	config_group_init_type_name(&dev->dev_stat_grps.scsi_lu_group,
			"scsi_lu", &target_stat_scsi_lu_cit);
	configfs_add_default_group(&dev->dev_stat_grps.scsi_lu_group,
			&dev->dev_stat_grps.stat_group);
}