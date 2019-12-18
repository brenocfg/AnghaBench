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
typedef  scalar_t__ u64 ;
struct xpc_partition {int /*<<< orphan*/  references; int /*<<< orphan*/  teardown_wq; int /*<<< orphan*/  setup_state; int /*<<< orphan*/  disengage_timer; int /*<<< orphan*/  act_state; int /*<<< orphan*/  act_lock; scalar_t__ activate_IRQ_rcvd; } ;
struct TYPE_2__ {int (* setup_partitions ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ L1_CACHE_ALIGN (scalar_t__) ; 
 int /*<<< orphan*/  XPC_P_AS_INACTIVE ; 
 int /*<<< orphan*/  XPC_P_SS_UNSET ; 
 int /*<<< orphan*/  XPC_SET_REASON (struct xpc_partition*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct xpc_partition* kcalloc (short,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int stub1 () ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 short xp_max_npartitions ; 
 TYPE_1__ xpc_arch_ops ; 
 int /*<<< orphan*/  xpc_part ; 
 struct xpc_partition* xpc_partitions ; 
 int /*<<< orphan*/  xpc_timeout_partition_disengage ; 

__attribute__((used)) static int
xpc_setup_partitions(void)
{
	short partid;
	struct xpc_partition *part;

	xpc_partitions = kcalloc(xp_max_npartitions,
				 sizeof(struct xpc_partition),
				 GFP_KERNEL);
	if (xpc_partitions == NULL) {
		dev_err(xpc_part, "can't get memory for partition structure\n");
		return -ENOMEM;
	}

	/*
	 * The first few fields of each entry of xpc_partitions[] need to
	 * be initialized now so that calls to xpc_connect() and
	 * xpc_disconnect() can be made prior to the activation of any remote
	 * partition. NOTE THAT NONE OF THE OTHER FIELDS BELONGING TO THESE
	 * ENTRIES ARE MEANINGFUL UNTIL AFTER AN ENTRY'S CORRESPONDING
	 * PARTITION HAS BEEN ACTIVATED.
	 */
	for (partid = 0; partid < xp_max_npartitions; partid++) {
		part = &xpc_partitions[partid];

		DBUG_ON((u64)part != L1_CACHE_ALIGN((u64)part));

		part->activate_IRQ_rcvd = 0;
		spin_lock_init(&part->act_lock);
		part->act_state = XPC_P_AS_INACTIVE;
		XPC_SET_REASON(part, 0, 0);

		timer_setup(&part->disengage_timer,
			    xpc_timeout_partition_disengage, 0);

		part->setup_state = XPC_P_SS_UNSET;
		init_waitqueue_head(&part->teardown_wq);
		atomic_set(&part->references, 0);
	}

	return xpc_arch_ops.setup_partitions();
}