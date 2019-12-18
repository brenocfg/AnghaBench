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
struct sym_tcb {int dummy; } ;
struct TYPE_2__ {scalar_t__ reqtags; } ;
struct sym_lcb {TYPE_1__ s; } ;
struct sym_hcb {struct sym_tcb* target; } ;
struct sym_ccb {int dummy; } ;
struct scsi_device {size_t id; int /*<<< orphan*/  lun; } ;
struct scsi_cmnd {struct scsi_device* device; } ;

/* Variables and functions */
 int M_SIMPLE_TAG ; 
 struct sym_ccb* sym_get_ccb (struct sym_hcb*,struct scsi_cmnd*,int) ; 
 struct sym_lcb* sym_lp (struct sym_tcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_queue_scsiio (struct sym_hcb*,struct scsi_cmnd*,struct sym_ccb*) ; 

__attribute__((used)) static int sym_queue_command(struct sym_hcb *np, struct scsi_cmnd *cmd)
{
	struct scsi_device *sdev = cmd->device;
	struct sym_tcb *tp;
	struct sym_lcb *lp;
	struct sym_ccb *cp;
	int	order;

	/*
	 *  Retrieve the target descriptor.
	 */
	tp = &np->target[sdev->id];

	/*
	 *  Select tagged/untagged.
	 */
	lp = sym_lp(tp, sdev->lun);
	order = (lp && lp->s.reqtags) ? M_SIMPLE_TAG : 0;

	/*
	 *  Queue the SCSI IO.
	 */
	cp = sym_get_ccb(np, cmd, order);
	if (!cp)
		return 1;	/* Means resource shortage */
	sym_queue_scsiio(np, cmd, cp);
	return 0;
}