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
struct hinic_sq_task {int /*<<< orphan*/  pkt_info0; } ;

/* Variables and functions */
 int /*<<< orphan*/  HINIC_SQ_TASK_INFO0_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L2HDR_LEN ; 

void hinic_task_set_l2hdr(struct hinic_sq_task *task, u32 len)
{
	task->pkt_info0 |= HINIC_SQ_TASK_INFO0_SET(len, L2HDR_LEN);
}