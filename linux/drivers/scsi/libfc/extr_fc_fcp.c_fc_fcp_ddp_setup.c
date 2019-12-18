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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {scalar_t__ (* ddp_setup ) (struct fc_lport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct fc_lport {TYPE_1__ tt; scalar_t__ lro_enabled; } ;
struct fc_fcp_pkt {int req_flags; int /*<<< orphan*/  xfer_ddp; int /*<<< orphan*/  cmd; struct fc_lport* lp; } ;

/* Variables and functions */
 int FC_SRB_READ ; 
 int /*<<< orphan*/  scsi_sg_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_sglist (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct fc_lport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void fc_fcp_ddp_setup(struct fc_fcp_pkt *fsp, u16 xid)
{
	struct fc_lport *lport;

	lport = fsp->lp;
	if ((fsp->req_flags & FC_SRB_READ) &&
	    (lport->lro_enabled) && (lport->tt.ddp_setup)) {
		if (lport->tt.ddp_setup(lport, xid, scsi_sglist(fsp->cmd),
					scsi_sg_count(fsp->cmd)))
			fsp->xfer_ddp = xid;
	}
}