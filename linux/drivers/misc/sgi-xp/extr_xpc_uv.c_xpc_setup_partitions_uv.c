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
struct xpc_partition_uv {int /*<<< orphan*/  remote_act_state; int /*<<< orphan*/  flags_lock; int /*<<< orphan*/  cached_activate_gru_mq_desc_mutex; } ;
struct TYPE_3__ {struct xpc_partition_uv uv; } ;
struct TYPE_4__ {TYPE_1__ sn; } ;

/* Variables and functions */
 int /*<<< orphan*/  XPC_P_AS_INACTIVE ; 
 short XP_MAX_NPARTITIONS_UV ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 TYPE_2__* xpc_partitions ; 

__attribute__((used)) static int
xpc_setup_partitions_uv(void)
{
	short partid;
	struct xpc_partition_uv *part_uv;

	for (partid = 0; partid < XP_MAX_NPARTITIONS_UV; partid++) {
		part_uv = &xpc_partitions[partid].sn.uv;

		mutex_init(&part_uv->cached_activate_gru_mq_desc_mutex);
		spin_lock_init(&part_uv->flags_lock);
		part_uv->remote_act_state = XPC_P_AS_INACTIVE;
	}
	return 0;
}