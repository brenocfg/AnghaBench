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
typedef  int uint64_t ;
struct v9_sdma_mqd {int sdmax_rlcx_rb_cntl; int sdmax_rlcx_doorbell_offset; int /*<<< orphan*/  sdmax_rlcx_dummy_reg; int /*<<< orphan*/  sdma_queue_id; int /*<<< orphan*/  sdma_engine_id; void* sdmax_rlcx_rb_rptr_addr_hi; void* sdmax_rlcx_rb_rptr_addr_lo; void* sdmax_rlcx_rb_base_hi; void* sdmax_rlcx_rb_base; } ;
struct queue_properties {int queue_size; int vmid; int queue_address; int doorbell_off; int /*<<< orphan*/  is_active; int /*<<< orphan*/  sdma_queue_id; int /*<<< orphan*/  sdma_engine_id; scalar_t__ read_ptr; } ;
struct mqd_manager {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_IS_ACTIVE (struct queue_properties) ; 
 int SDMA0_RLC0_DOORBELL_OFFSET__OFFSET__SHIFT ; 
 int SDMA0_RLC0_RB_CNTL__RB_SIZE__SHIFT ; 
 int SDMA0_RLC0_RB_CNTL__RB_VMID__SHIFT ; 
 int SDMA0_RLC0_RB_CNTL__RPTR_WRITEBACK_ENABLE__SHIFT ; 
 int SDMA0_RLC0_RB_CNTL__RPTR_WRITEBACK_TIMER__SHIFT ; 
 int /*<<< orphan*/  SDMA_RLC_DUMMY_DEFAULT ; 
 struct v9_sdma_mqd* get_sdma_mqd (void*) ; 
 void* lower_32_bits (int) ; 
 int order_base_2 (int) ; 
 void* upper_32_bits (int) ; 

__attribute__((used)) static void update_mqd_sdma(struct mqd_manager *mm, void *mqd,
		struct queue_properties *q)
{
	struct v9_sdma_mqd *m;

	m = get_sdma_mqd(mqd);
	m->sdmax_rlcx_rb_cntl = order_base_2(q->queue_size / 4)
		<< SDMA0_RLC0_RB_CNTL__RB_SIZE__SHIFT |
		q->vmid << SDMA0_RLC0_RB_CNTL__RB_VMID__SHIFT |
		1 << SDMA0_RLC0_RB_CNTL__RPTR_WRITEBACK_ENABLE__SHIFT |
		6 << SDMA0_RLC0_RB_CNTL__RPTR_WRITEBACK_TIMER__SHIFT;

	m->sdmax_rlcx_rb_base = lower_32_bits(q->queue_address >> 8);
	m->sdmax_rlcx_rb_base_hi = upper_32_bits(q->queue_address >> 8);
	m->sdmax_rlcx_rb_rptr_addr_lo = lower_32_bits((uint64_t)q->read_ptr);
	m->sdmax_rlcx_rb_rptr_addr_hi = upper_32_bits((uint64_t)q->read_ptr);
	m->sdmax_rlcx_doorbell_offset =
		q->doorbell_off << SDMA0_RLC0_DOORBELL_OFFSET__OFFSET__SHIFT;

	m->sdma_engine_id = q->sdma_engine_id;
	m->sdma_queue_id = q->sdma_queue_id;
	m->sdmax_rlcx_dummy_reg = SDMA_RLC_DUMMY_DEFAULT;

	q->is_active = QUEUE_IS_ACTIVE(*q);
}