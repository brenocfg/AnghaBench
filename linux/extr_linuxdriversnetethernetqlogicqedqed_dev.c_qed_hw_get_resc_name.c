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
typedef  enum qed_resources { ____Placeholder_qed_resources } qed_resources ;

/* Variables and functions */
#define  QED_BDQ 141 
#define  QED_CMDQS_CQS 140 
#define  QED_ILT 139 
#define  QED_L2_QUEUE 138 
#define  QED_LL2_QUEUE 137 
#define  QED_MAC 136 
#define  QED_PQ 135 
#define  QED_RDMA_CNQ_RAM 134 
#define  QED_RDMA_STATS_QUEUE 133 
#define  QED_RL 132 
#define  QED_RSS_ENG 131 
#define  QED_SB 130 
#define  QED_VLAN 129 
#define  QED_VPORT 128 

const char *qed_hw_get_resc_name(enum qed_resources res_id)
{
	switch (res_id) {
	case QED_L2_QUEUE:
		return "L2_QUEUE";
	case QED_VPORT:
		return "VPORT";
	case QED_RSS_ENG:
		return "RSS_ENG";
	case QED_PQ:
		return "PQ";
	case QED_RL:
		return "RL";
	case QED_MAC:
		return "MAC";
	case QED_VLAN:
		return "VLAN";
	case QED_RDMA_CNQ_RAM:
		return "RDMA_CNQ_RAM";
	case QED_ILT:
		return "ILT";
	case QED_LL2_QUEUE:
		return "LL2_QUEUE";
	case QED_CMDQS_CQS:
		return "CMDQS_CQS";
	case QED_RDMA_STATS_QUEUE:
		return "RDMA_STATS_QUEUE";
	case QED_BDQ:
		return "BDQ";
	case QED_SB:
		return "SB";
	default:
		return "UNKNOWN_RESOURCE";
	}
}