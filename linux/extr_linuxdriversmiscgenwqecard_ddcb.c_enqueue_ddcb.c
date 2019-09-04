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
struct genwqe_dev {int dummy; } ;
struct ddcb_queue {int ddcb_max; int /*<<< orphan*/  IO_QUEUE_OFFSET; struct ddcb* ddcb_vaddr; } ;
struct ddcb {int icrc_hsi_shi_32; } ;
typedef  int __be32 ;

/* Variables and functions */
 int DDCB_COMPLETED_BE32 ; 
 int DDCB_NEXT_BE32 ; 
 int RET_DDCB_APPENDED ; 
 int RET_DDCB_TAPPED ; 
 int /*<<< orphan*/  __genwqe_writeq (struct genwqe_dev*,int /*<<< orphan*/ ,int) ; 
 int cmpxchg (int*,int,int) ; 
 int /*<<< orphan*/  ddcb_mark_appended (struct ddcb*) ; 
 int /*<<< orphan*/  ddcb_mark_tapped (struct ddcb*) ; 
 int /*<<< orphan*/  ddcb_mark_unused (struct ddcb*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int enqueue_ddcb(struct genwqe_dev *cd, struct ddcb_queue *queue,
			struct ddcb *pddcb, int ddcb_no)
{
	unsigned int try;
	int prev_no;
	struct ddcb *prev_ddcb;
	__be32 old, new, icrc_hsi_shi;
	u64 num;

	/*
	 * For performance checks a Dispatch Timestamp can be put into
	 * DDCB It is supposed to use the SLU's free running counter,
	 * but this requires PCIe cycles.
	 */
	ddcb_mark_unused(pddcb);

	/* check previous DDCB if already fetched */
	prev_no = (ddcb_no == 0) ? queue->ddcb_max - 1 : ddcb_no - 1;
	prev_ddcb = &queue->ddcb_vaddr[prev_no];

	/*
	 * It might have happened that the HSI.FETCHED bit is
	 * set. Retry in this case. Therefore I expect maximum 2 times
	 * trying.
	 */
	ddcb_mark_appended(pddcb);
	for (try = 0; try < 2; try++) {
		old = prev_ddcb->icrc_hsi_shi_32; /* read SHI/HSI in BE32 */

		/* try to append via NEXT bit if prev DDCB is not completed */
		if ((old & DDCB_COMPLETED_BE32) != 0x00000000)
			break;

		new = (old | DDCB_NEXT_BE32);

		wmb();		/* need to ensure write ordering */
		icrc_hsi_shi = cmpxchg(&prev_ddcb->icrc_hsi_shi_32, old, new);

		if (icrc_hsi_shi == old)
			return RET_DDCB_APPENDED; /* appended to queue */
	}

	/* Queue must be re-started by updating QUEUE_OFFSET */
	ddcb_mark_tapped(pddcb);
	num = (u64)ddcb_no << 8;

	wmb();			/* need to ensure write ordering */
	__genwqe_writeq(cd, queue->IO_QUEUE_OFFSET, num); /* start queue */

	return RET_DDCB_TAPPED;
}