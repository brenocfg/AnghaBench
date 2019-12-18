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
typedef  int u32 ;
struct hinic_sq_task {int pkt_info2; } ;
typedef  enum hinic_l3_offload_type { ____Placeholder_hinic_l3_offload_type } hinic_l3_offload_type ;

/* Variables and functions */
 int HINIC_SQ_TASK_INFO2_SET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTER_L3LEN ; 
 int /*<<< orphan*/  OUTER_L3TYPE ; 

void hinic_task_set_outter_l3(struct hinic_sq_task *task,
			      enum hinic_l3_offload_type l3_type,
			      u32 network_len)
{
	task->pkt_info2 |= HINIC_SQ_TASK_INFO2_SET(l3_type, OUTER_L3TYPE) |
			   HINIC_SQ_TASK_INFO2_SET(network_len, OUTER_L3LEN);
}