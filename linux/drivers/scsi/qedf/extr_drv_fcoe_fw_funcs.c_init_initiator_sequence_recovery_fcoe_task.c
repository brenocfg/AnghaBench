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
typedef  int /*<<< orphan*/  u32 ;
struct fcoe_task_params {TYPE_2__* sqe; } ;
struct TYPE_3__ {int /*<<< orphan*/  seq_rec_updated_offset; } ;
struct TYPE_4__ {TYPE_1__ additional_info_union; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCOE_SEQUENCE_RECOVERY ; 
 int /*<<< orphan*/  init_common_sqe (struct fcoe_task_params*,int /*<<< orphan*/ ) ; 

int init_initiator_sequence_recovery_fcoe_task(
	struct fcoe_task_params *task_params, u32 desired_offset)
{
	init_common_sqe(task_params, FCOE_SEQUENCE_RECOVERY);
	task_params->sqe->additional_info_union.seq_rec_updated_offset =
								desired_offset;
	return 0;
}