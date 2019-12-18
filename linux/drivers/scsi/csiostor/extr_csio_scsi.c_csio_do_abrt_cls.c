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
struct csio_scsi_qset {int /*<<< orphan*/  eq_idx; } ;
struct csio_lnode {size_t portid; } ;
struct csio_ioreq {int /*<<< orphan*/  eq_idx; int /*<<< orphan*/  tmo; struct csio_lnode* lnode; } ;
struct csio_hw {struct csio_scsi_qset** sqset; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_SCSI_ABRT_TMO_MS ; 
 int SCSI_ABORT ; 
 int csio_scsi_abort (struct csio_ioreq*) ; 
 int csio_scsi_close (struct csio_ioreq*) ; 
 int smp_processor_id () ; 

__attribute__((used)) static int
csio_do_abrt_cls(struct csio_hw *hw, struct csio_ioreq *ioreq, bool abort)
{
	int rv;
	int cpu = smp_processor_id();
	struct csio_lnode *ln = ioreq->lnode;
	struct csio_scsi_qset *sqset = &hw->sqset[ln->portid][cpu];

	ioreq->tmo = CSIO_SCSI_ABRT_TMO_MS;
	/*
	 * Use current processor queue for posting the abort/close, but retain
	 * the ingress queue ID of the original I/O being aborted/closed - we
	 * need the abort/close completion to be received on the same queue
	 * as the original I/O.
	 */
	ioreq->eq_idx = sqset->eq_idx;

	if (abort == SCSI_ABORT)
		rv = csio_scsi_abort(ioreq);
	else
		rv = csio_scsi_close(ioreq);

	return rv;
}