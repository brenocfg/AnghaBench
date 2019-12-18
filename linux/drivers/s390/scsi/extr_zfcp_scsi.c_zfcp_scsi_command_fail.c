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
struct scsi_cmnd {int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  set_host_byte (struct scsi_cmnd*,int) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  zfcp_dbf_scsi_fail_send (struct scsi_cmnd*) ; 

__attribute__((used)) static void zfcp_scsi_command_fail(struct scsi_cmnd *scpnt, int result)
{
	set_host_byte(scpnt, result);
	zfcp_dbf_scsi_fail_send(scpnt);
	scpnt->scsi_done(scpnt);
}