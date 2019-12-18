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
typedef  int uint64_t ;
struct vi_mqd {int cp_hqd_pq_control; int cp_hqd_pq_doorbell_control; unsigned int cp_hqd_eop_control; unsigned int cp_hqd_ib_control; unsigned int cp_hqd_iq_timer; unsigned int cp_hqd_ctx_save_control; int /*<<< orphan*/  cp_hqd_vmid; void* cp_hqd_eop_base_addr_hi; void* cp_hqd_eop_base_addr_lo; void* cp_hqd_pq_wptr_poll_addr_hi; void* cp_hqd_pq_wptr_poll_addr_lo; void* cp_hqd_pq_rptr_report_addr_hi; void* cp_hqd_pq_rptr_report_addr_lo; void* cp_hqd_pq_base_hi; void* cp_hqd_pq_base_lo; } ;
struct queue_properties {int queue_size; int doorbell_off; int eop_ring_buffer_size; int eop_ring_buffer_address; scalar_t__ format; int /*<<< orphan*/  is_active; scalar_t__ ctx_save_restore_area_address; int /*<<< orphan*/  vmid; scalar_t__ write_ptr; scalar_t__ read_ptr; scalar_t__ queue_address; } ;
struct mqd_manager {TYPE_1__* dev; } ;
struct TYPE_2__ {scalar_t__ cwsr_enabled; } ;

/* Variables and functions */
 unsigned int CP_HQD_CTX_SAVE_CONTROL__ATC__SHIFT ; 
 unsigned int CP_HQD_CTX_SAVE_CONTROL__MTYPE__SHIFT ; 
 unsigned int CP_HQD_EOP_CONTROL__EOP_ATC__SHIFT ; 
 unsigned int CP_HQD_EOP_CONTROL__MTYPE__SHIFT ; 
 unsigned int CP_HQD_IB_CONTROL__IB_ATC__SHIFT ; 
 int CP_HQD_IB_CONTROL__MIN_IB_AVAIL_SIZE__SHIFT ; 
 unsigned int CP_HQD_IB_CONTROL__MTYPE__SHIFT ; 
 unsigned int CP_HQD_IQ_TIMER__IQ_ATC__SHIFT ; 
 unsigned int CP_HQD_IQ_TIMER__MTYPE__SHIFT ; 
 unsigned int CP_HQD_PQ_CONTROL__MTYPE__SHIFT ; 
 int CP_HQD_PQ_CONTROL__NO_UPDATE_RPTR_MASK ; 
 unsigned int CP_HQD_PQ_CONTROL__PQ_ATC__SHIFT ; 
 int CP_HQD_PQ_CONTROL__RPTR_BLOCK_SIZE__SHIFT ; 
 int CP_HQD_PQ_CONTROL__SLOT_BASED_WPTR__SHIFT ; 
 int CP_HQD_PQ_DOORBELL_CONTROL__DOORBELL_OFFSET__SHIFT ; 
 scalar_t__ KFD_QUEUE_FORMAT_AQL ; 
 int /*<<< orphan*/  QUEUE_IS_ACTIVE (struct queue_properties) ; 
 struct vi_mqd* get_mqd (void*) ; 
 void* lower_32_bits (int) ; 
 unsigned int min (int,int) ; 
 int order_base_2 (int) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  set_priority (struct vi_mqd*,struct queue_properties*) ; 
 int /*<<< orphan*/  update_cu_mask (struct mqd_manager*,void*,struct queue_properties*) ; 
 void* upper_32_bits (int) ; 

__attribute__((used)) static void __update_mqd(struct mqd_manager *mm, void *mqd,
			struct queue_properties *q, unsigned int mtype,
			unsigned int atc_bit)
{
	struct vi_mqd *m;

	m = get_mqd(mqd);

	m->cp_hqd_pq_control = 5 << CP_HQD_PQ_CONTROL__RPTR_BLOCK_SIZE__SHIFT |
			atc_bit << CP_HQD_PQ_CONTROL__PQ_ATC__SHIFT |
			mtype << CP_HQD_PQ_CONTROL__MTYPE__SHIFT;
	m->cp_hqd_pq_control |=	order_base_2(q->queue_size / 4) - 1;
	pr_debug("cp_hqd_pq_control 0x%x\n", m->cp_hqd_pq_control);

	m->cp_hqd_pq_base_lo = lower_32_bits((uint64_t)q->queue_address >> 8);
	m->cp_hqd_pq_base_hi = upper_32_bits((uint64_t)q->queue_address >> 8);

	m->cp_hqd_pq_rptr_report_addr_lo = lower_32_bits((uint64_t)q->read_ptr);
	m->cp_hqd_pq_rptr_report_addr_hi = upper_32_bits((uint64_t)q->read_ptr);
	m->cp_hqd_pq_wptr_poll_addr_lo = lower_32_bits((uint64_t)q->write_ptr);
	m->cp_hqd_pq_wptr_poll_addr_hi = upper_32_bits((uint64_t)q->write_ptr);

	m->cp_hqd_pq_doorbell_control =
		q->doorbell_off <<
			CP_HQD_PQ_DOORBELL_CONTROL__DOORBELL_OFFSET__SHIFT;
	pr_debug("cp_hqd_pq_doorbell_control 0x%x\n",
			m->cp_hqd_pq_doorbell_control);

	m->cp_hqd_eop_control = atc_bit << CP_HQD_EOP_CONTROL__EOP_ATC__SHIFT |
			mtype << CP_HQD_EOP_CONTROL__MTYPE__SHIFT;

	m->cp_hqd_ib_control = atc_bit << CP_HQD_IB_CONTROL__IB_ATC__SHIFT |
			3 << CP_HQD_IB_CONTROL__MIN_IB_AVAIL_SIZE__SHIFT |
			mtype << CP_HQD_IB_CONTROL__MTYPE__SHIFT;

	/*
	 * HW does not clamp this field correctly. Maximum EOP queue size
	 * is constrained by per-SE EOP done signal count, which is 8-bit.
	 * Limit is 0xFF EOP entries (= 0x7F8 dwords). CP will not submit
	 * more than (EOP entry count - 1) so a queue size of 0x800 dwords
	 * is safe, giving a maximum field value of 0xA.
	 */
	m->cp_hqd_eop_control |= min(0xA,
		order_base_2(q->eop_ring_buffer_size / 4) - 1);
	m->cp_hqd_eop_base_addr_lo =
			lower_32_bits(q->eop_ring_buffer_address >> 8);
	m->cp_hqd_eop_base_addr_hi =
			upper_32_bits(q->eop_ring_buffer_address >> 8);

	m->cp_hqd_iq_timer = atc_bit << CP_HQD_IQ_TIMER__IQ_ATC__SHIFT |
			mtype << CP_HQD_IQ_TIMER__MTYPE__SHIFT;

	m->cp_hqd_vmid = q->vmid;

	if (q->format == KFD_QUEUE_FORMAT_AQL) {
		m->cp_hqd_pq_control |= CP_HQD_PQ_CONTROL__NO_UPDATE_RPTR_MASK |
				2 << CP_HQD_PQ_CONTROL__SLOT_BASED_WPTR__SHIFT;
	}

	if (mm->dev->cwsr_enabled && q->ctx_save_restore_area_address)
		m->cp_hqd_ctx_save_control =
			atc_bit << CP_HQD_CTX_SAVE_CONTROL__ATC__SHIFT |
			mtype << CP_HQD_CTX_SAVE_CONTROL__MTYPE__SHIFT;

	update_cu_mask(mm, mqd, q);
	set_priority(m, q);

	q->is_active = QUEUE_IS_ACTIVE(*q);
}