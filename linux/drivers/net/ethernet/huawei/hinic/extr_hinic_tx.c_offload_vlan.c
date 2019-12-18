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
typedef  unsigned int u16 ;
struct hinic_sq_task {int pkt_info0; } ;

/* Variables and functions */
 int /*<<< orphan*/  HINIC_SQ_CTRL_SET (unsigned int,int /*<<< orphan*/ ) ; 
 int HINIC_SQ_TASK_INFO0_SET (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QUEUE_INFO_PRI ; 
 int /*<<< orphan*/  VLAN_OFFLOAD ; 
 int /*<<< orphan*/  VLAN_TAG ; 

__attribute__((used)) static void offload_vlan(struct hinic_sq_task *task, u32 *queue_info,
			 u16 vlan_tag, u16 vlan_pri)
{
	task->pkt_info0 |= HINIC_SQ_TASK_INFO0_SET(vlan_tag, VLAN_TAG) |
				HINIC_SQ_TASK_INFO0_SET(1U, VLAN_OFFLOAD);

	*queue_info |= HINIC_SQ_CTRL_SET(vlan_pri, QUEUE_INFO_PRI);
}