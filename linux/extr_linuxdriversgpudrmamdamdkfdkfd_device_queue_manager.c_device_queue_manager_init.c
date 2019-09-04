#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kfd_dev {TYPE_1__* device_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* initialize ) (struct device_queue_manager*) ;int /*<<< orphan*/  restore_process_queues; int /*<<< orphan*/  evict_process_queues; int /*<<< orphan*/  process_termination; void* set_trap_handler; void* set_cache_memory_policy; void* uninitialize; void* unregister_process; void* register_process; void* get_mqd_manager; void* update_queue; int /*<<< orphan*/  destroy_queue; int /*<<< orphan*/  create_queue; int /*<<< orphan*/  stop; int /*<<< orphan*/  start; int /*<<< orphan*/  destroy_kernel_queue; int /*<<< orphan*/  create_kernel_queue; } ;
struct device_queue_manager {int sched_policy; TYPE_2__ ops; int /*<<< orphan*/  asic_ops; struct kfd_dev* dev; } ;
struct TYPE_3__ {int asic_family; } ;

/* Variables and functions */
#define  CHIP_CARRIZO 139 
#define  CHIP_FIJI 138 
#define  CHIP_HAWAII 137 
#define  CHIP_KAVERI 136 
#define  CHIP_POLARIS10 135 
#define  CHIP_POLARIS11 134 
#define  CHIP_RAVEN 133 
#define  CHIP_TONGA 132 
#define  CHIP_VEGA10 131 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  KFD_SCHED_POLICY_HWS 130 
#define  KFD_SCHED_POLICY_HWS_NO_OVERSUBSCRIPTION 129 
#define  KFD_SCHED_POLICY_NO_HWS 128 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  create_kernel_queue_cpsch ; 
 int /*<<< orphan*/  create_queue_cpsch ; 
 int /*<<< orphan*/  create_queue_nocpsch ; 
 int /*<<< orphan*/  destroy_kernel_queue_cpsch ; 
 int /*<<< orphan*/  destroy_queue_cpsch ; 
 int /*<<< orphan*/  destroy_queue_nocpsch ; 
 int /*<<< orphan*/  device_queue_manager_init_cik (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_queue_manager_init_cik_hawaii (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_queue_manager_init_v9 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_queue_manager_init_vi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_queue_manager_init_vi_tonga (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evict_process_queues_cpsch ; 
 int /*<<< orphan*/  evict_process_queues_nocpsch ; 
 void* get_mqd_manager ; 
 int /*<<< orphan*/  initialize_cpsch (struct device_queue_manager*) ; 
 int /*<<< orphan*/  initialize_nocpsch (struct device_queue_manager*) ; 
 int /*<<< orphan*/  kfree (struct device_queue_manager*) ; 
 struct device_queue_manager* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  process_termination_cpsch ; 
 int /*<<< orphan*/  process_termination_nocpsch ; 
 void* register_process ; 
 int /*<<< orphan*/  restore_process_queues_cpsch ; 
 int /*<<< orphan*/  restore_process_queues_nocpsch ; 
 int sched_policy ; 
 void* set_cache_memory_policy ; 
 void* set_trap_handler ; 
 int /*<<< orphan*/  start_cpsch ; 
 int /*<<< orphan*/  start_nocpsch ; 
 int /*<<< orphan*/  stop_cpsch ; 
 int /*<<< orphan*/  stop_nocpsch ; 
 int /*<<< orphan*/  stub1 (struct device_queue_manager*) ; 
 void* uninitialize ; 
 void* unregister_process ; 
 void* update_queue ; 

struct device_queue_manager *device_queue_manager_init(struct kfd_dev *dev)
{
	struct device_queue_manager *dqm;

	pr_debug("Loading device queue manager\n");

	dqm = kzalloc(sizeof(*dqm), GFP_KERNEL);
	if (!dqm)
		return NULL;

	switch (dev->device_info->asic_family) {
	/* HWS is not available on Hawaii. */
	case CHIP_HAWAII:
	/* HWS depends on CWSR for timely dequeue. CWSR is not
	 * available on Tonga.
	 *
	 * FIXME: This argument also applies to Kaveri.
	 */
	case CHIP_TONGA:
		dqm->sched_policy = KFD_SCHED_POLICY_NO_HWS;
		break;
	default:
		dqm->sched_policy = sched_policy;
		break;
	}

	dqm->dev = dev;
	switch (dqm->sched_policy) {
	case KFD_SCHED_POLICY_HWS:
	case KFD_SCHED_POLICY_HWS_NO_OVERSUBSCRIPTION:
		/* initialize dqm for cp scheduling */
		dqm->ops.create_queue = create_queue_cpsch;
		dqm->ops.initialize = initialize_cpsch;
		dqm->ops.start = start_cpsch;
		dqm->ops.stop = stop_cpsch;
		dqm->ops.destroy_queue = destroy_queue_cpsch;
		dqm->ops.update_queue = update_queue;
		dqm->ops.get_mqd_manager = get_mqd_manager;
		dqm->ops.register_process = register_process;
		dqm->ops.unregister_process = unregister_process;
		dqm->ops.uninitialize = uninitialize;
		dqm->ops.create_kernel_queue = create_kernel_queue_cpsch;
		dqm->ops.destroy_kernel_queue = destroy_kernel_queue_cpsch;
		dqm->ops.set_cache_memory_policy = set_cache_memory_policy;
		dqm->ops.set_trap_handler = set_trap_handler;
		dqm->ops.process_termination = process_termination_cpsch;
		dqm->ops.evict_process_queues = evict_process_queues_cpsch;
		dqm->ops.restore_process_queues = restore_process_queues_cpsch;
		break;
	case KFD_SCHED_POLICY_NO_HWS:
		/* initialize dqm for no cp scheduling */
		dqm->ops.start = start_nocpsch;
		dqm->ops.stop = stop_nocpsch;
		dqm->ops.create_queue = create_queue_nocpsch;
		dqm->ops.destroy_queue = destroy_queue_nocpsch;
		dqm->ops.update_queue = update_queue;
		dqm->ops.get_mqd_manager = get_mqd_manager;
		dqm->ops.register_process = register_process;
		dqm->ops.unregister_process = unregister_process;
		dqm->ops.initialize = initialize_nocpsch;
		dqm->ops.uninitialize = uninitialize;
		dqm->ops.set_cache_memory_policy = set_cache_memory_policy;
		dqm->ops.set_trap_handler = set_trap_handler;
		dqm->ops.process_termination = process_termination_nocpsch;
		dqm->ops.evict_process_queues = evict_process_queues_nocpsch;
		dqm->ops.restore_process_queues =
			restore_process_queues_nocpsch;
		break;
	default:
		pr_err("Invalid scheduling policy %d\n", dqm->sched_policy);
		goto out_free;
	}

	switch (dev->device_info->asic_family) {
	case CHIP_CARRIZO:
		device_queue_manager_init_vi(&dqm->asic_ops);
		break;

	case CHIP_KAVERI:
		device_queue_manager_init_cik(&dqm->asic_ops);
		break;

	case CHIP_HAWAII:
		device_queue_manager_init_cik_hawaii(&dqm->asic_ops);
		break;

	case CHIP_TONGA:
	case CHIP_FIJI:
	case CHIP_POLARIS10:
	case CHIP_POLARIS11:
		device_queue_manager_init_vi_tonga(&dqm->asic_ops);
		break;

	case CHIP_VEGA10:
	case CHIP_RAVEN:
		device_queue_manager_init_v9(&dqm->asic_ops);
		break;
	default:
		WARN(1, "Unexpected ASIC family %u",
		     dev->device_info->asic_family);
		goto out_free;
	}

	if (!dqm->ops.initialize(dqm))
		return dqm;

out_free:
	kfree(dqm);
	return NULL;
}