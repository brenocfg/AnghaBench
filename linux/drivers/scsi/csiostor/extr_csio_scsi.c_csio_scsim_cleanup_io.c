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
struct csio_scsim {int /*<<< orphan*/  active_q; struct csio_hw* hw; } ;
struct csio_hw {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_DB_ASSERT (scalar_t__) ; 
 int /*<<< orphan*/  CSIO_SCSI_ABORT_Q_POLL_MS ; 
 int DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_dbg (struct csio_hw*,char*) ; 
 int csio_scsi_abort_io_q (struct csio_scsim*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  csio_scsi_cleanup_io_q (struct csio_scsim*,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int
csio_scsim_cleanup_io(struct csio_scsim *scm, bool abort)
{
	struct csio_hw *hw = scm->hw;
	int rv = 0;
	int count = DIV_ROUND_UP(60 * 1000, CSIO_SCSI_ABORT_Q_POLL_MS);

	/* No I/Os pending */
	if (list_empty(&scm->active_q))
		return 0;

	/* Wait until all active I/Os are completed */
	while (!list_empty(&scm->active_q) && count--) {
		spin_unlock_irq(&hw->lock);
		msleep(CSIO_SCSI_ABORT_Q_POLL_MS);
		spin_lock_irq(&hw->lock);
	}

	/* all I/Os completed */
	if (list_empty(&scm->active_q))
		return 0;

	/* Else abort */
	if (abort) {
		rv = csio_scsi_abort_io_q(scm, &scm->active_q, 30000);
		if (rv == 0)
			return rv;
		csio_dbg(hw, "Some I/O aborts timed out, cleaning up..\n");
	}

	csio_scsi_cleanup_io_q(scm, &scm->active_q);

	CSIO_DB_ASSERT(list_empty(&scm->active_q));

	return rv;
}