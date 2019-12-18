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
struct bnxt_re_dev {int num_msix; struct bnxt_qplib_nq* nq; struct bnxt_qplib_rcfw rcfw; } ;
struct bnxt_qplib_nq {int dummy; } ;

/* Variables and functions */
 int BNXT_RE_NQ_IDX ; 
 int /*<<< orphan*/  bnxt_qplib_nq_stop_irq (struct bnxt_qplib_nq*,int) ; 
 int /*<<< orphan*/  bnxt_qplib_rcfw_stop_irq (struct bnxt_qplib_rcfw*,int) ; 

__attribute__((used)) static void bnxt_re_stop_irq(void *handle)
{
	struct bnxt_re_dev *rdev = (struct bnxt_re_dev *)handle;
	struct bnxt_qplib_rcfw *rcfw = &rdev->rcfw;
	struct bnxt_qplib_nq *nq;
	int indx;

	for (indx = BNXT_RE_NQ_IDX; indx < rdev->num_msix; indx++) {
		nq = &rdev->nq[indx - 1];
		bnxt_qplib_nq_stop_irq(nq, false);
	}

	bnxt_qplib_rcfw_stop_irq(rcfw, false);
}