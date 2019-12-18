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
typedef  enum resource_id_enum { ____Placeholder_resource_id_enum } resource_id_enum ;
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
 int RESOURCE_BDQ_E ; 
 int RESOURCE_CQS_E ; 
 int RESOURCE_ILT_E ; 
 int RESOURCE_LL2_QUEUE_E ; 
 int RESOURCE_NUM_INVALID ; 
 int RESOURCE_NUM_L2_QUEUE_E ; 
 int RESOURCE_NUM_PQ_E ; 
 int RESOURCE_NUM_RL_E ; 
 int RESOURCE_NUM_RSS_ENGINES_E ; 
 int RESOURCE_NUM_SB_E ; 
 int RESOURCE_NUM_VPORT_E ; 
 int RESOURCE_RDMA_STATS_QUEUE_E ; 
 int RESOURCE_VFC_FILTER_E ; 

__attribute__((used)) static enum resource_id_enum qed_mcp_get_mfw_res_id(enum qed_resources res_id)
{
	enum resource_id_enum mfw_res_id = RESOURCE_NUM_INVALID;

	switch (res_id) {
	case QED_SB:
		mfw_res_id = RESOURCE_NUM_SB_E;
		break;
	case QED_L2_QUEUE:
		mfw_res_id = RESOURCE_NUM_L2_QUEUE_E;
		break;
	case QED_VPORT:
		mfw_res_id = RESOURCE_NUM_VPORT_E;
		break;
	case QED_RSS_ENG:
		mfw_res_id = RESOURCE_NUM_RSS_ENGINES_E;
		break;
	case QED_PQ:
		mfw_res_id = RESOURCE_NUM_PQ_E;
		break;
	case QED_RL:
		mfw_res_id = RESOURCE_NUM_RL_E;
		break;
	case QED_MAC:
	case QED_VLAN:
		/* Each VFC resource can accommodate both a MAC and a VLAN */
		mfw_res_id = RESOURCE_VFC_FILTER_E;
		break;
	case QED_ILT:
		mfw_res_id = RESOURCE_ILT_E;
		break;
	case QED_LL2_QUEUE:
		mfw_res_id = RESOURCE_LL2_QUEUE_E;
		break;
	case QED_RDMA_CNQ_RAM:
	case QED_CMDQS_CQS:
		/* CNQ/CMDQS are the same resource */
		mfw_res_id = RESOURCE_CQS_E;
		break;
	case QED_RDMA_STATS_QUEUE:
		mfw_res_id = RESOURCE_RDMA_STATS_QUEUE_E;
		break;
	case QED_BDQ:
		mfw_res_id = RESOURCE_BDQ_E;
		break;
	default:
		break;
	}

	return mfw_res_id;
}