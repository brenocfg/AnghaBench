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
struct v9_mqd {int header; int compute_pipelinestat_enable; int compute_static_thread_mgmt_se0; int compute_static_thread_mgmt_se1; int compute_static_thread_mgmt_se2; int compute_static_thread_mgmt_se3; int cp_hqd_persistent_state; int cp_mqd_control; int cp_hqd_quantum; int cp_hqd_pipe_priority; int cp_hqd_queue_priority; int cp_hqd_aql_control; int compute_pgm_rsrc2; int cp_hqd_cntl_stack_size; int cp_hqd_cntl_stack_offset; int cp_hqd_wg_state_offset; int /*<<< orphan*/  cp_hqd_ctx_save_size; void* cp_hqd_ctx_save_base_addr_hi; void* cp_hqd_ctx_save_base_addr_lo; void* cp_mqd_base_addr_hi; void* cp_mqd_base_addr_lo; } ;
struct queue_properties {scalar_t__ type; int ctl_stack_size; scalar_t__ format; int /*<<< orphan*/  ctx_save_restore_area_size; scalar_t__ ctx_save_restore_area_address; scalar_t__ tba_addr; } ;
struct mqd_manager {int (* update_mqd ) (struct mqd_manager*,struct v9_mqd*,struct queue_properties*) ;struct kfd_dev* dev; } ;
struct kfd_mem_obj {scalar_t__ gpu_addr; scalar_t__ cpu_ptr; int /*<<< orphan*/  gtt_mem; } ;
struct kfd_dev {scalar_t__ cwsr_enabled; int /*<<< orphan*/  kgd; TYPE_1__* kfd2kgd; } ;
struct TYPE_2__ {int (* init_gtt_mem_allocation ) (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__*,void*,int) ;} ;

/* Variables and functions */
 scalar_t__ ALIGN (int,int /*<<< orphan*/ ) ; 
 int COMPUTE_PGM_RSRC2__TRAP_PRESENT__SHIFT ; 
 int CP_HQD_AQL_CONTROL__CONTROL0__SHIFT ; 
 int CP_HQD_PERSISTENT_STATE__PRELOAD_REQ_MASK ; 
 int CP_HQD_PERSISTENT_STATE__PRELOAD_SIZE__SHIFT ; 
 int CP_HQD_PERSISTENT_STATE__QSWITCH_MODE__SHIFT ; 
 int CP_HQD_QUANTUM__QUANTUM_DURATION__SHIFT ; 
 int CP_HQD_QUANTUM__QUANTUM_EN__SHIFT ; 
 int CP_HQD_QUANTUM__QUANTUM_SCALE__SHIFT ; 
 int CP_MQD_CONTROL__PRIV_STATE__SHIFT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ KFD_QUEUE_FORMAT_AQL ; 
 scalar_t__ KFD_QUEUE_TYPE_COMPUTE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int kfd_gtt_sa_allocate (struct kfd_dev*,int,struct kfd_mem_obj**) ; 
 struct kfd_mem_obj* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* lower_32_bits (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct v9_mqd*,int /*<<< orphan*/ ,int) ; 
 int stub1 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__*,void*,int) ; 
 int stub2 (struct mqd_manager*,struct v9_mqd*,struct queue_properties*) ; 
 void* upper_32_bits (scalar_t__) ; 

__attribute__((used)) static int init_mqd(struct mqd_manager *mm, void **mqd,
			struct kfd_mem_obj **mqd_mem_obj, uint64_t *gart_addr,
			struct queue_properties *q)
{
	int retval;
	uint64_t addr;
	struct v9_mqd *m;
	struct kfd_dev *kfd = mm->dev;

	/* From V9,  for CWSR, the control stack is located on the next page
	 * boundary after the mqd, we will use the gtt allocation function
	 * instead of sub-allocation function.
	 */
	if (kfd->cwsr_enabled && (q->type == KFD_QUEUE_TYPE_COMPUTE)) {
		*mqd_mem_obj = kzalloc(sizeof(struct kfd_mem_obj), GFP_KERNEL);
		if (!*mqd_mem_obj)
			return -ENOMEM;
		retval = kfd->kfd2kgd->init_gtt_mem_allocation(kfd->kgd,
			ALIGN(q->ctl_stack_size, PAGE_SIZE) +
				ALIGN(sizeof(struct v9_mqd), PAGE_SIZE),
			&((*mqd_mem_obj)->gtt_mem),
			&((*mqd_mem_obj)->gpu_addr),
			(void *)&((*mqd_mem_obj)->cpu_ptr), true);
	} else
		retval = kfd_gtt_sa_allocate(mm->dev, sizeof(struct v9_mqd),
				mqd_mem_obj);
	if (retval != 0)
		return -ENOMEM;

	m = (struct v9_mqd *) (*mqd_mem_obj)->cpu_ptr;
	addr = (*mqd_mem_obj)->gpu_addr;

	memset(m, 0, sizeof(struct v9_mqd));

	m->header = 0xC0310800;
	m->compute_pipelinestat_enable = 1;
	m->compute_static_thread_mgmt_se0 = 0xFFFFFFFF;
	m->compute_static_thread_mgmt_se1 = 0xFFFFFFFF;
	m->compute_static_thread_mgmt_se2 = 0xFFFFFFFF;
	m->compute_static_thread_mgmt_se3 = 0xFFFFFFFF;

	m->cp_hqd_persistent_state = CP_HQD_PERSISTENT_STATE__PRELOAD_REQ_MASK |
			0x53 << CP_HQD_PERSISTENT_STATE__PRELOAD_SIZE__SHIFT;

	m->cp_mqd_control = 1 << CP_MQD_CONTROL__PRIV_STATE__SHIFT;

	m->cp_mqd_base_addr_lo        = lower_32_bits(addr);
	m->cp_mqd_base_addr_hi        = upper_32_bits(addr);

	m->cp_hqd_quantum = 1 << CP_HQD_QUANTUM__QUANTUM_EN__SHIFT |
			1 << CP_HQD_QUANTUM__QUANTUM_SCALE__SHIFT |
			10 << CP_HQD_QUANTUM__QUANTUM_DURATION__SHIFT;

	m->cp_hqd_pipe_priority = 1;
	m->cp_hqd_queue_priority = 15;

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
	retval = mm->update_mqd(mm, m, q);

	return retval;
}