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
typedef  unsigned long long u64 ;
struct genwqe_dev {int dummy; } ;
struct ddcb_queue {size_t ddcb_next; int ddcb_max; int /*<<< orphan*/  ddcb_seq; struct ddcb* ddcb_vaddr; } ;
struct ddcb {int icrc_hsi_shi_32; int /*<<< orphan*/  seqnum_16; int /*<<< orphan*/  pre; } ;

/* Variables and functions */
 int DDCB_COMPLETED_BE32 ; 
 int /*<<< orphan*/  DDCB_PRESET_PRE ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 scalar_t__ queue_free_ddcbs (struct ddcb_queue*) ; 

__attribute__((used)) static struct ddcb *get_next_ddcb(struct genwqe_dev *cd,
				  struct ddcb_queue *queue,
				  int *num)
{
	u64 *pu64;
	struct ddcb *pddcb;

	if (queue_free_ddcbs(queue) == 0) /* queue is  full */
		return NULL;

	/* find new ddcb */
	pddcb = &queue->ddcb_vaddr[queue->ddcb_next];

	/* if it is not completed, we are not allowed to use it */
	/* barrier(); */
	if ((pddcb->icrc_hsi_shi_32 & DDCB_COMPLETED_BE32) == 0x00000000)
		return NULL;

	*num = queue->ddcb_next;	/* internal DDCB number */
	queue->ddcb_next = (queue->ddcb_next + 1) % queue->ddcb_max;

	/* clear important DDCB fields */
	pu64 = (u64 *)pddcb;
	pu64[0] = 0ULL;		/* offs 0x00 (ICRC,HSI,SHI,...) */
	pu64[1] = 0ULL;		/* offs 0x01 (ACFUNC,CMD...) */

	/* destroy previous results in ASV */
	pu64[0x80/8] = 0ULL;	/* offs 0x80 (ASV + 0) */
	pu64[0x88/8] = 0ULL;	/* offs 0x88 (ASV + 0x08) */
	pu64[0x90/8] = 0ULL;	/* offs 0x90 (ASV + 0x10) */
	pu64[0x98/8] = 0ULL;	/* offs 0x98 (ASV + 0x18) */
	pu64[0xd0/8] = 0ULL;	/* offs 0xd0 (RETC,ATTN...) */

	pddcb->pre = DDCB_PRESET_PRE; /* 128 */
	pddcb->seqnum_16 = cpu_to_be16(queue->ddcb_seq++);
	return pddcb;
}