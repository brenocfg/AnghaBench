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
struct hinic_sq_task {int pkt_info0; int pkt_info1; int pkt_info2; scalar_t__ zero_pad; int /*<<< orphan*/  pkt_info4; scalar_t__ ufo_v6_identify; } ;

/* Variables and functions */
 int /*<<< orphan*/  HINIC_L2TYPE_ETH ; 
 int /*<<< orphan*/  HINIC_L4_OFF_DISABLE ; 
 int /*<<< orphan*/  HINIC_MEDIA_UNKNOWN ; 
 int /*<<< orphan*/  HINIC_OUTER_L3TYPE_UNKNOWN ; 
 int /*<<< orphan*/  HINIC_PKT_NOT_PARSED ; 
 int HINIC_SQ_TASK_INFO0_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int HINIC_SQ_TASK_INFO1_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int HINIC_SQ_TASK_INFO2_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HINIC_SQ_TASK_INFO4_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HINIC_TUNNEL_L4TYPE_UNKNOWN ; 
 int /*<<< orphan*/  HINIC_VLAN_OFF_DISABLE ; 
 int /*<<< orphan*/  INNER_L3TYPE ; 
 int /*<<< orphan*/  INNER_L3_LEN ; 
 int /*<<< orphan*/  INNER_L4_LEN ; 
 int /*<<< orphan*/  L2HDR_LEN ; 
 int /*<<< orphan*/  L2TYPE ; 
 int /*<<< orphan*/  L4_OFFLOAD ; 
 int /*<<< orphan*/  MEDIA_TYPE ; 
 int /*<<< orphan*/  OUTER_L3TYPE ; 
 int /*<<< orphan*/  OUTER_L3_LEN ; 
 int /*<<< orphan*/  PARSE_FLAG ; 
 int /*<<< orphan*/  TUNNEL_L4TYPE ; 
 int /*<<< orphan*/  TUNNEL_L4_LEN ; 
 int /*<<< orphan*/  VLAN_OFFLOAD ; 

__attribute__((used)) static void sq_prepare_task(struct hinic_sq_task *task)
{
	task->pkt_info0 =
		HINIC_SQ_TASK_INFO0_SET(0, L2HDR_LEN) |
		HINIC_SQ_TASK_INFO0_SET(HINIC_L4_OFF_DISABLE, L4_OFFLOAD) |
		HINIC_SQ_TASK_INFO0_SET(HINIC_OUTER_L3TYPE_UNKNOWN,
					INNER_L3TYPE) |
		HINIC_SQ_TASK_INFO0_SET(HINIC_VLAN_OFF_DISABLE,
					VLAN_OFFLOAD) |
		HINIC_SQ_TASK_INFO0_SET(HINIC_PKT_NOT_PARSED, PARSE_FLAG);

	task->pkt_info1 =
		HINIC_SQ_TASK_INFO1_SET(HINIC_MEDIA_UNKNOWN, MEDIA_TYPE) |
		HINIC_SQ_TASK_INFO1_SET(0, INNER_L4_LEN) |
		HINIC_SQ_TASK_INFO1_SET(0, INNER_L3_LEN);

	task->pkt_info2 =
		HINIC_SQ_TASK_INFO2_SET(0, TUNNEL_L4_LEN) |
		HINIC_SQ_TASK_INFO2_SET(0, OUTER_L3_LEN)  |
		HINIC_SQ_TASK_INFO2_SET(HINIC_TUNNEL_L4TYPE_UNKNOWN,
					TUNNEL_L4TYPE)    |
		HINIC_SQ_TASK_INFO2_SET(HINIC_OUTER_L3TYPE_UNKNOWN,
					OUTER_L3TYPE);

	task->ufo_v6_identify = 0;

	task->pkt_info4 = HINIC_SQ_TASK_INFO4_SET(HINIC_L2TYPE_ETH, L2TYPE);

	task->zero_pad = 0;
}