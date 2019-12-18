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
typedef  int u64 ;
struct ntb_transport_qp {int /*<<< orphan*/  link_work; int /*<<< orphan*/  link_cleanup; } ;
struct ntb_transport_ctx {int qp_bitmap; int qp_bitmap_free; unsigned int qp_count; unsigned int mw_count; int /*<<< orphan*/  ndev; int /*<<< orphan*/  link_work; int /*<<< orphan*/  link_is_up; struct ntb_transport_qp* qp_vec; } ;

/* Variables and functions */
 int BIT_ULL (unsigned int) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntb_free_mw (struct ntb_transport_ctx*,unsigned int) ; 
 int /*<<< orphan*/  ntb_qp_link_cleanup (struct ntb_transport_qp*) ; 
 unsigned int ntb_spad_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_spad_write (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ntb_transport_link_cleanup(struct ntb_transport_ctx *nt)
{
	struct ntb_transport_qp *qp;
	u64 qp_bitmap_alloc;
	unsigned int i, count;

	qp_bitmap_alloc = nt->qp_bitmap & ~nt->qp_bitmap_free;

	/* Pass along the info to any clients */
	for (i = 0; i < nt->qp_count; i++)
		if (qp_bitmap_alloc & BIT_ULL(i)) {
			qp = &nt->qp_vec[i];
			ntb_qp_link_cleanup(qp);
			cancel_work_sync(&qp->link_cleanup);
			cancel_delayed_work_sync(&qp->link_work);
		}

	if (!nt->link_is_up)
		cancel_delayed_work_sync(&nt->link_work);

	for (i = 0; i < nt->mw_count; i++)
		ntb_free_mw(nt, i);

	/* The scratchpad registers keep the values if the remote side
	 * goes down, blast them now to give them a sane value the next
	 * time they are accessed
	 */
	count = ntb_spad_count(nt->ndev);
	for (i = 0; i < count; i++)
		ntb_spad_write(nt->ndev, i, 0);
}