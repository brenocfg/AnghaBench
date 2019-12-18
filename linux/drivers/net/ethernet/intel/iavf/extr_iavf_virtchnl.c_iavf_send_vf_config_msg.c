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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct iavf_adapter {int /*<<< orphan*/  aq_required; int /*<<< orphan*/  current_op; } ;
typedef  int /*<<< orphan*/  caps ;

/* Variables and functions */
 int /*<<< orphan*/  IAVF_FLAG_AQ_GET_CONFIG ; 
 scalar_t__ PF_IS_V11 (struct iavf_adapter*) ; 
 int /*<<< orphan*/  VIRTCHNL_OP_GET_VF_RESOURCES ; 
 int VIRTCHNL_VF_OFFLOAD_ADQ ; 
 int VIRTCHNL_VF_OFFLOAD_ENCAP ; 
 int VIRTCHNL_VF_OFFLOAD_ENCAP_CSUM ; 
 int VIRTCHNL_VF_OFFLOAD_L2 ; 
 int VIRTCHNL_VF_OFFLOAD_REQ_QUEUES ; 
 int VIRTCHNL_VF_OFFLOAD_RSS_AQ ; 
 int VIRTCHNL_VF_OFFLOAD_RSS_PCTYPE_V2 ; 
 int VIRTCHNL_VF_OFFLOAD_RSS_PF ; 
 int VIRTCHNL_VF_OFFLOAD_RSS_REG ; 
 int VIRTCHNL_VF_OFFLOAD_VLAN ; 
 int VIRTCHNL_VF_OFFLOAD_WB_ON_ITR ; 
 int iavf_send_pf_msg (struct iavf_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int iavf_send_vf_config_msg(struct iavf_adapter *adapter)
{
	u32 caps;

	caps = VIRTCHNL_VF_OFFLOAD_L2 |
	       VIRTCHNL_VF_OFFLOAD_RSS_PF |
	       VIRTCHNL_VF_OFFLOAD_RSS_AQ |
	       VIRTCHNL_VF_OFFLOAD_RSS_REG |
	       VIRTCHNL_VF_OFFLOAD_VLAN |
	       VIRTCHNL_VF_OFFLOAD_WB_ON_ITR |
	       VIRTCHNL_VF_OFFLOAD_RSS_PCTYPE_V2 |
	       VIRTCHNL_VF_OFFLOAD_ENCAP |
	       VIRTCHNL_VF_OFFLOAD_ENCAP_CSUM |
	       VIRTCHNL_VF_OFFLOAD_REQ_QUEUES |
	       VIRTCHNL_VF_OFFLOAD_ADQ;

	adapter->current_op = VIRTCHNL_OP_GET_VF_RESOURCES;
	adapter->aq_required &= ~IAVF_FLAG_AQ_GET_CONFIG;
	if (PF_IS_V11(adapter))
		return iavf_send_pf_msg(adapter, VIRTCHNL_OP_GET_VF_RESOURCES,
					(u8 *)&caps, sizeof(caps));
	else
		return iavf_send_pf_msg(adapter, VIRTCHNL_OP_GET_VF_RESOURCES,
					NULL, 0);
}