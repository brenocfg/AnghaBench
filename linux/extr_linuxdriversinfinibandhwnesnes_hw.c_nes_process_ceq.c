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
typedef  int u64 ;
typedef  size_t u32 ;
struct nes_hw_cq {int /*<<< orphan*/  (* ce_handler ) (struct nes_device*,struct nes_hw_cq*) ;} ;
struct nes_hw_ceq {size_t ceq_head; size_t ceq_size; TYPE_1__* ceq_vbase; } ;
struct nes_device {int dummy; } ;
struct TYPE_2__ {scalar_t__* ceqe_words; } ;

/* Variables and functions */
 size_t NES_CEQE_CQ_CTX_HIGH_IDX ; 
 size_t NES_CEQE_CQ_CTX_LOW_IDX ; 
 int NES_CEQE_VALID ; 
 int /*<<< orphan*/  barrier () ; 
 int le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct nes_device*,struct nes_hw_cq*) ; 

__attribute__((used)) static void nes_process_ceq(struct nes_device *nesdev, struct nes_hw_ceq *ceq)
{
	u64 u64temp;
	struct nes_hw_cq *cq;
	u32 head;
	u32 ceq_size;

	/* nes_debug(NES_DBG_CQ, "\n"); */
	head = ceq->ceq_head;
	ceq_size = ceq->ceq_size;

	do {
		if (le32_to_cpu(ceq->ceq_vbase[head].ceqe_words[NES_CEQE_CQ_CTX_HIGH_IDX]) &
				NES_CEQE_VALID) {
			u64temp = (((u64)(le32_to_cpu(ceq->ceq_vbase[head].ceqe_words[NES_CEQE_CQ_CTX_HIGH_IDX]))) << 32) |
						((u64)(le32_to_cpu(ceq->ceq_vbase[head].ceqe_words[NES_CEQE_CQ_CTX_LOW_IDX])));
			u64temp <<= 1;
			cq = *((struct nes_hw_cq **)&u64temp);
			/* nes_debug(NES_DBG_CQ, "pCQ = %p\n", cq); */
			barrier();
			ceq->ceq_vbase[head].ceqe_words[NES_CEQE_CQ_CTX_HIGH_IDX] = 0;

			/* call the event handler */
			cq->ce_handler(nesdev, cq);

			if (++head >= ceq_size)
				head = 0;
		} else {
			break;
		}

	} while (1);

	ceq->ceq_head = head;
}