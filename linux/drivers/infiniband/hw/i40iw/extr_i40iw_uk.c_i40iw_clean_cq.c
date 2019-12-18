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
typedef  int u8 ;
typedef  scalar_t__ u64 ;
typedef  size_t u32 ;
struct i40iw_extended_cqe {int dummy; } ;
struct TYPE_2__ {size_t head; size_t size; } ;
struct i40iw_cq_uk {int polarity; TYPE_1__ cq_ring; int /*<<< orphan*/ * cq_base; scalar_t__ avoid_mem_cflct; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_CQ_VALID ; 
 scalar_t__ RS_64 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_64bit_val (scalar_t__*,int,scalar_t__*) ; 
 int /*<<< orphan*/  set_64bit_val (scalar_t__*,int,int /*<<< orphan*/ ) ; 

void i40iw_clean_cq(void *queue, struct i40iw_cq_uk *cq)
{
	u64 *cqe;
	u64 qword3, comp_ctx;
	u32 cq_head;
	u8 polarity, temp;

	cq_head = cq->cq_ring.head;
	temp = cq->polarity;
	do {
		if (cq->avoid_mem_cflct)
			cqe = (u64 *)&(((struct i40iw_extended_cqe *)cq->cq_base)[cq_head]);
		else
			cqe = (u64 *)&cq->cq_base[cq_head];
		get_64bit_val(cqe, 24, &qword3);
		polarity = (u8)RS_64(qword3, I40IW_CQ_VALID);

		if (polarity != temp)
			break;

		get_64bit_val(cqe, 8, &comp_ctx);
		if ((void *)(unsigned long)comp_ctx == queue)
			set_64bit_val(cqe, 8, 0);

		cq_head = (cq_head + 1) % cq->cq_ring.size;
		if (!cq_head)
			temp ^= 1;
	} while (true);
}