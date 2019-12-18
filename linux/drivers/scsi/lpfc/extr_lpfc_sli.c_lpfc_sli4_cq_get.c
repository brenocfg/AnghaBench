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
struct lpfc_queue {scalar_t__ qe_valid; int /*<<< orphan*/  host_index; } ;
struct lpfc_cqe {int dummy; } ;

/* Variables and functions */
 scalar_t__ bf_get_le32 (int /*<<< orphan*/ ,struct lpfc_cqe*) ; 
 int /*<<< orphan*/  lpfc_cqe_valid ; 
 struct lpfc_cqe* lpfc_sli4_qe (struct lpfc_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct lpfc_cqe *
lpfc_sli4_cq_get(struct lpfc_queue *q)
{
	struct lpfc_cqe *cqe;

	/* sanity check on queue memory */
	if (unlikely(!q))
		return NULL;
	cqe = lpfc_sli4_qe(q, q->host_index);

	/* If the next CQE is not valid then we are done */
	if (bf_get_le32(lpfc_cqe_valid, cqe) != q->qe_valid)
		return NULL;

	/*
	 * insert barrier for instruction interlock : data from the hardware
	 * must have the valid bit checked before it can be copied and acted
	 * upon. Given what was seen in lpfc_sli4_cq_get() of speculative
	 * instructions allowing action on content before valid bit checked,
	 * add barrier here as well. May not be needed as "content" is a
	 * single 32-bit entity here (vs multi word structure for cq's).
	 */
	mb();
	return cqe;
}