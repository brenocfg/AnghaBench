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
struct scsi_cmnd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  scsi_del_cmd_from_list (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_mq_free_sgtables (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_uninit_cmd (struct scsi_cmnd*) ; 

__attribute__((used)) static void scsi_mq_uninit_cmd(struct scsi_cmnd *cmd)
{
	scsi_mq_free_sgtables(cmd);
	scsi_uninit_cmd(cmd);
	scsi_del_cmd_from_list(cmd);
}