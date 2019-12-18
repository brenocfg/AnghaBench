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
typedef  int /*<<< orphan*/  u32 ;
struct hinic_sq_task {int /*<<< orphan*/  pkt_info1; int /*<<< orphan*/  pkt_info0; } ;
typedef  enum hinic_l3_offload_type { ____Placeholder_hinic_l3_offload_type } hinic_l3_offload_type ;

/* Variables and functions */
 int /*<<< orphan*/  HINIC_SQ_TASK_INFO0_SET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HINIC_SQ_TASK_INFO1_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INNER_L3LEN ; 
 int /*<<< orphan*/  INNER_L3TYPE ; 

void hinic_task_set_inner_l3(struct hinic_sq_task *task,
			     enum hinic_l3_offload_type l3_type,
			     u32 network_len)
{
	task->pkt_info0 |= HINIC_SQ_TASK_INFO0_SET(l3_type, INNER_L3TYPE);
	task->pkt_info1 |= HINIC_SQ_TASK_INFO1_SET(network_len, INNER_L3LEN);
}