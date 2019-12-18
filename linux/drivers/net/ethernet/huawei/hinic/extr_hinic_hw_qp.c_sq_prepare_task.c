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
struct hinic_sq_task {scalar_t__ zero_pad; int /*<<< orphan*/  pkt_info4; scalar_t__ ufo_v6_identify; scalar_t__ pkt_info2; scalar_t__ pkt_info1; scalar_t__ pkt_info0; } ;

/* Variables and functions */
 int /*<<< orphan*/  HINIC_L2TYPE_ETH ; 
 int /*<<< orphan*/  HINIC_SQ_TASK_INFO4_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L2TYPE ; 

__attribute__((used)) static void sq_prepare_task(struct hinic_sq_task *task)
{
	task->pkt_info0 = 0;
	task->pkt_info1 = 0;
	task->pkt_info2 = 0;

	task->ufo_v6_identify = 0;

	task->pkt_info4 = HINIC_SQ_TASK_INFO4_SET(HINIC_L2TYPE_ETH, L2TYPE);

	task->zero_pad = 0;
}