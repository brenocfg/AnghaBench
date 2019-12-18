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
struct qedf_fastpath {int /*<<< orphan*/  sb_info; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IGU_INT_DISABLE ; 
 int /*<<< orphan*/  IGU_INT_ENABLE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  qed_sb_ack (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qed_sb_update_sb_idx (int /*<<< orphan*/ ) ; 
 scalar_t__ qedf_fp_has_work (struct qedf_fastpath*) ; 
 int /*<<< orphan*/  qedf_process_completions (struct qedf_fastpath*) ; 
 int /*<<< orphan*/  rmb () ; 

__attribute__((used)) static irqreturn_t qedf_msix_handler(int irq, void *dev_id)
{
	struct qedf_fastpath *fp = dev_id;

	if (!fp) {
		QEDF_ERR(NULL, "fp is null.\n");
		return IRQ_HANDLED;
	}
	if (!fp->sb_info) {
		QEDF_ERR(NULL, "fp->sb_info in null.");
		return IRQ_HANDLED;
	}

	/*
	 * Disable interrupts for this status block while we process new
	 * completions
	 */
	qed_sb_ack(fp->sb_info, IGU_INT_DISABLE, 0 /*do not update*/);

	while (1) {
		qedf_process_completions(fp);

		if (qedf_fp_has_work(fp) == 0) {
			/* Update the sb information */
			qed_sb_update_sb_idx(fp->sb_info);

			/* Check for more work */
			rmb();

			if (qedf_fp_has_work(fp) == 0) {
				/* Re-enable interrupts */
				qed_sb_ack(fp->sb_info, IGU_INT_ENABLE, 1);
				return IRQ_HANDLED;
			}
		}
	}

	/* Do we ever want to break out of above loop? */
	return IRQ_HANDLED;
}