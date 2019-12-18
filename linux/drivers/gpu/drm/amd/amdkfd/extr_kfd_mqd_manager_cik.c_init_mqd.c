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
typedef  int /*<<< orphan*/  uint64_t ;
struct queue_properties {scalar_t__ format; } ;
struct mqd_manager {int /*<<< orphan*/  (* update_mqd ) (struct mqd_manager*,struct cik_mqd*,struct queue_properties*) ;} ;
struct kfd_mem_obj {int /*<<< orphan*/  gpu_addr; scalar_t__ cpu_ptr; } ;
struct cik_mqd {int header; int compute_pipelinestat_enable; int compute_static_thread_mgmt_se0; int compute_static_thread_mgmt_se1; int compute_static_thread_mgmt_se2; int compute_static_thread_mgmt_se3; int cp_hqd_persistent_state; int cp_hqd_quantum; int /*<<< orphan*/  cp_hqd_iq_rptr; int /*<<< orphan*/  cp_mqd_base_addr_hi; int /*<<< orphan*/  cp_mqd_base_addr_lo; int /*<<< orphan*/  cp_mqd_control; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int,int) ; 
 int /*<<< orphan*/  AQL_ENABLE ; 
 int DEFAULT_CP_HQD_PERSISTENT_STATE ; 
 scalar_t__ KFD_QUEUE_FORMAT_AQL ; 
 int /*<<< orphan*/  MQD_CONTROL_PRIV_STATE_EN ; 
 int PRELOAD_REQ ; 
 int QUANTUM_DURATION (int) ; 
 int QUANTUM_EN ; 
 int QUANTUM_SCALE_1MS ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct cik_mqd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_priority (struct cik_mqd*,struct queue_properties*) ; 
 int /*<<< orphan*/  stub1 (struct mqd_manager*,struct cik_mqd*,struct queue_properties*) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_mqd(struct mqd_manager *mm, void **mqd,
		struct kfd_mem_obj *mqd_mem_obj, uint64_t *gart_addr,
		struct queue_properties *q)
{
	uint64_t addr;
	struct cik_mqd *m;

	m = (struct cik_mqd *) mqd_mem_obj->cpu_ptr;
	addr = mqd_mem_obj->gpu_addr;

	memset(m, 0, ALIGN(sizeof(struct cik_mqd), 256));

	m->header = 0xC0310800;
	m->compute_pipelinestat_enable = 1;
	m->compute_static_thread_mgmt_se0 = 0xFFFFFFFF;
	m->compute_static_thread_mgmt_se1 = 0xFFFFFFFF;
	m->compute_static_thread_mgmt_se2 = 0xFFFFFFFF;
	m->compute_static_thread_mgmt_se3 = 0xFFFFFFFF;

	/*
	 * Make sure to use the last queue state saved on mqd when the cp
	 * reassigns the queue, so when queue is switched on/off (e.g over
	 * subscription or quantum timeout) the context will be consistent
	 */
	m->cp_hqd_persistent_state =
				DEFAULT_CP_HQD_PERSISTENT_STATE | PRELOAD_REQ;

	m->cp_mqd_control             = MQD_CONTROL_PRIV_STATE_EN;
	m->cp_mqd_base_addr_lo        = lower_32_bits(addr);
	m->cp_mqd_base_addr_hi        = upper_32_bits(addr);

	m->cp_hqd_quantum = QUANTUM_EN | QUANTUM_SCALE_1MS |
				QUANTUM_DURATION(10);

	/*
	 * Pipe Priority
	 * Identifies the pipe relative priority when this queue is connected
	 * to the pipeline. The pipe priority is against the GFX pipe and HP3D.
	 * In KFD we are using a fixed pipe priority set to CS_MEDIUM.
	 * 0 = CS_LOW (typically below GFX)
	 * 1 = CS_MEDIUM (typically between HP3D and GFX
	 * 2 = CS_HIGH (typically above HP3D)
	 */
	set_priority(m, q);

	if (q->format == KFD_QUEUE_FORMAT_AQL)
		m->cp_hqd_iq_rptr = AQL_ENABLE;

	*mqd = m;
	if (gart_addr)
		*gart_addr = addr;
	mm->update_mqd(mm, m, q);
}