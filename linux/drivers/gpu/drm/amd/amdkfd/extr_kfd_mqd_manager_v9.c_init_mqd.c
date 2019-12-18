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
typedef  scalar_t__ uint64_t ;
struct v9_mqd {int header; int compute_pipelinestat_enable; int compute_static_thread_mgmt_se0; int compute_static_thread_mgmt_se1; int compute_static_thread_mgmt_se2; int compute_static_thread_mgmt_se3; int compute_static_thread_mgmt_se4; int compute_static_thread_mgmt_se5; int compute_static_thread_mgmt_se6; int compute_static_thread_mgmt_se7; int cp_hqd_persistent_state; int cp_mqd_control; int cp_hqd_quantum; int cp_hqd_aql_control; int compute_pgm_rsrc2; int /*<<< orphan*/  cp_hqd_wg_state_offset; int /*<<< orphan*/  cp_hqd_cntl_stack_offset; int /*<<< orphan*/  cp_hqd_cntl_stack_size; int /*<<< orphan*/  cp_hqd_ctx_save_size; void* cp_hqd_ctx_save_base_addr_hi; void* cp_hqd_ctx_save_base_addr_lo; void* cp_mqd_base_addr_hi; void* cp_mqd_base_addr_lo; } ;
struct queue_properties {scalar_t__ format; int /*<<< orphan*/  ctl_stack_size; int /*<<< orphan*/  ctx_save_restore_area_size; scalar_t__ ctx_save_restore_area_address; scalar_t__ tba_addr; } ;
struct mqd_manager {int /*<<< orphan*/  (* update_mqd ) (struct mqd_manager*,struct v9_mqd*,struct queue_properties*) ;TYPE_1__* dev; } ;
struct kfd_mem_obj {scalar_t__ gpu_addr; scalar_t__ cpu_ptr; } ;
struct TYPE_2__ {scalar_t__ cwsr_enabled; } ;

/* Variables and functions */
 int COMPUTE_PGM_RSRC2__TRAP_PRESENT__SHIFT ; 
 int CP_HQD_AQL_CONTROL__CONTROL0__SHIFT ; 
 int CP_HQD_PERSISTENT_STATE__PRELOAD_REQ_MASK ; 
 int CP_HQD_PERSISTENT_STATE__PRELOAD_SIZE__SHIFT ; 
 int CP_HQD_PERSISTENT_STATE__QSWITCH_MODE__SHIFT ; 
 int CP_HQD_QUANTUM__QUANTUM_DURATION__SHIFT ; 
 int CP_HQD_QUANTUM__QUANTUM_EN__SHIFT ; 
 int CP_HQD_QUANTUM__QUANTUM_SCALE__SHIFT ; 
 int CP_MQD_CONTROL__PRIV_STATE__SHIFT ; 
 scalar_t__ KFD_QUEUE_FORMAT_AQL ; 
 void* lower_32_bits (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct v9_mqd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct mqd_manager*,struct v9_mqd*,struct queue_properties*) ; 
 void* upper_32_bits (scalar_t__) ; 

__attribute__((used)) static void init_mqd(struct mqd_manager *mm, void **mqd,
			struct kfd_mem_obj *mqd_mem_obj, uint64_t *gart_addr,
			struct queue_properties *q)
{
	uint64_t addr;
	struct v9_mqd *m;

	m = (struct v9_mqd *) mqd_mem_obj->cpu_ptr;
	addr = mqd_mem_obj->gpu_addr;

	memset(m, 0, sizeof(struct v9_mqd));

	m->header = 0xC0310800;
	m->compute_pipelinestat_enable = 1;
	m->compute_static_thread_mgmt_se0 = 0xFFFFFFFF;
	m->compute_static_thread_mgmt_se1 = 0xFFFFFFFF;
	m->compute_static_thread_mgmt_se2 = 0xFFFFFFFF;
	m->compute_static_thread_mgmt_se3 = 0xFFFFFFFF;
	m->compute_static_thread_mgmt_se4 = 0xFFFFFFFF;
	m->compute_static_thread_mgmt_se5 = 0xFFFFFFFF;
	m->compute_static_thread_mgmt_se6 = 0xFFFFFFFF;
	m->compute_static_thread_mgmt_se7 = 0xFFFFFFFF;

	m->cp_hqd_persistent_state = CP_HQD_PERSISTENT_STATE__PRELOAD_REQ_MASK |
			0x53 << CP_HQD_PERSISTENT_STATE__PRELOAD_SIZE__SHIFT;

	m->cp_mqd_control = 1 << CP_MQD_CONTROL__PRIV_STATE__SHIFT;

	m->cp_mqd_base_addr_lo        = lower_32_bits(addr);
	m->cp_mqd_base_addr_hi        = upper_32_bits(addr);

	m->cp_hqd_quantum = 1 << CP_HQD_QUANTUM__QUANTUM_EN__SHIFT |
			1 << CP_HQD_QUANTUM__QUANTUM_SCALE__SHIFT |
			10 << CP_HQD_QUANTUM__QUANTUM_DURATION__SHIFT;

	if (q->format == KFD_QUEUE_FORMAT_AQL) {
		m->cp_hqd_aql_control =
			1 << CP_HQD_AQL_CONTROL__CONTROL0__SHIFT;
	}

	if (q->tba_addr) {
		m->compute_pgm_rsrc2 |=
			(1 << COMPUTE_PGM_RSRC2__TRAP_PRESENT__SHIFT);
	}

	if (mm->dev->cwsr_enabled && q->ctx_save_restore_area_address) {
		m->cp_hqd_persistent_state |=
			(1 << CP_HQD_PERSISTENT_STATE__QSWITCH_MODE__SHIFT);
		m->cp_hqd_ctx_save_base_addr_lo =
			lower_32_bits(q->ctx_save_restore_area_address);
		m->cp_hqd_ctx_save_base_addr_hi =
			upper_32_bits(q->ctx_save_restore_area_address);
		m->cp_hqd_ctx_save_size = q->ctx_save_restore_area_size;
		m->cp_hqd_cntl_stack_size = q->ctl_stack_size;
		m->cp_hqd_cntl_stack_offset = q->ctl_stack_size;
		m->cp_hqd_wg_state_offset = q->ctl_stack_size;
	}

	*mqd = m;
	if (gart_addr)
		*gart_addr = addr;
	mm->update_mqd(mm, m, q);
}