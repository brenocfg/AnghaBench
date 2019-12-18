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
struct scsi_qla_host {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INIT_DONE ; 
 int /*<<< orphan*/  AF_ONLINE ; 
 int DID_NO_CONNECT ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql4_printk (int /*<<< orphan*/ ,struct scsi_qla_host*,char*) ; 
 int /*<<< orphan*/  qla4xxx_abort_active_cmds (struct scsi_qla_host*,int) ; 
 int /*<<< orphan*/  qla4xxx_mark_all_devices_missing (struct scsi_qla_host*) ; 

void qla4xxx_dead_adapter_cleanup(struct scsi_qla_host *ha)
{
	clear_bit(AF_ONLINE, &ha->flags);

	/* Disable the board */
	ql4_printk(KERN_INFO, ha, "Disabling the board\n");

	qla4xxx_abort_active_cmds(ha, DID_NO_CONNECT << 16);
	qla4xxx_mark_all_devices_missing(ha);
	clear_bit(AF_INIT_DONE, &ha->flags);
}