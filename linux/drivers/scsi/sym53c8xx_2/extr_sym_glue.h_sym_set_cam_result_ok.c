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
struct sym_ccb {int ssss_status; } ;
struct scsi_cmnd {int result; } ;

/* Variables and functions */
 int DID_OK ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,int) ; 

__attribute__((used)) static inline void sym_set_cam_result_ok(struct sym_ccb *cp, struct scsi_cmnd *cmd, int resid)
{
	scsi_set_resid(cmd, resid);
	cmd->result = (DID_OK << 16) | (cp->ssss_status & 0x7f);
}