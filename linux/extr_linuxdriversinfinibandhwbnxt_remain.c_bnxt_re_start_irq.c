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
struct bnxt_qplib_rcfw {int dummy; } ;
struct bnxt_re_dev {int num_msix; struct bnxt_qplib_nq* nq; struct bnxt_msix_entry* msix_entries; struct bnxt_qplib_rcfw rcfw; } ;
struct bnxt_qplib_nq {int dummy; } ;
struct bnxt_msix_entry {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 size_t BNXT_RE_AEQ_IDX ; 
 int BNXT_RE_NQ_IDX ; 
 int bnxt_qplib_nq_start_irq (struct bnxt_qplib_nq*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnxt_qplib_rcfw_start_irq (struct bnxt_qplib_rcfw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rdev_to_dev (struct bnxt_re_dev*) ; 

__attribute__((used)) static void bnxt_re_start_irq(void *handle, struct bnxt_msix_entry *ent)
{
	struct bnxt_re_dev *rdev = (struct bnxt_re_dev *)handle;
	struct bnxt_msix_entry *msix_ent = rdev->msix_entries;
	struct bnxt_qplib_rcfw *rcfw = &rdev->rcfw;
	struct bnxt_qplib_nq *nq;
	int indx, rc;

	if (!ent) {
		/* Not setting the f/w timeout bit in rcfw.
		 * During the driver unload the first command
		 * to f/w will timeout and that will set the
		 * timeout bit.
		 */
		dev_err(rdev_to_dev(rdev), "Failed to re-start IRQs\n");
		return;
	}

	/* Vectors may change after restart, so update with new vectors
	 * in device sctructure.
	 */
	for (indx = 0; indx < rdev->num_msix; indx++)
		rdev->msix_entries[indx].vector = ent[indx].vector;

	bnxt_qplib_rcfw_start_irq(rcfw, msix_ent[BNXT_RE_AEQ_IDX].vector,
				  false);
	for (indx = BNXT_RE_NQ_IDX ; indx < rdev->num_msix; indx++) {
		nq = &rdev->nq[indx - 1];
		rc = bnxt_qplib_nq_start_irq(nq, indx - 1,
					     msix_ent[indx].vector, false);
		if (rc)
			dev_warn(rdev_to_dev(rdev),
				 "Failed to reinit NQ index %d\n", indx - 1);
	}
}