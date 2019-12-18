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
struct TYPE_2__ {int /*<<< orphan*/  stat_group; int /*<<< orphan*/  scsi_transport_group; int /*<<< orphan*/  scsi_tgt_port_group; int /*<<< orphan*/  scsi_port_group; } ;
struct se_lun {TYPE_1__ port_stat_grps; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_group_init_type_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  configfs_add_default_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  target_stat_scsi_port_cit ; 
 int /*<<< orphan*/  target_stat_scsi_tgt_port_cit ; 
 int /*<<< orphan*/  target_stat_scsi_transport_cit ; 

void target_stat_setup_port_default_groups(struct se_lun *lun)
{
	config_group_init_type_name(&lun->port_stat_grps.scsi_port_group,
			"scsi_port", &target_stat_scsi_port_cit);
	configfs_add_default_group(&lun->port_stat_grps.scsi_port_group,
			&lun->port_stat_grps.stat_group);

	config_group_init_type_name(&lun->port_stat_grps.scsi_tgt_port_group,
			"scsi_tgt_port", &target_stat_scsi_tgt_port_cit);
	configfs_add_default_group(&lun->port_stat_grps.scsi_tgt_port_group,
			&lun->port_stat_grps.stat_group);

	config_group_init_type_name(&lun->port_stat_grps.scsi_transport_group,
			"scsi_transport", &target_stat_scsi_transport_cit);
	configfs_add_default_group(&lun->port_stat_grps.scsi_transport_group,
			&lun->port_stat_grps.stat_group);
}