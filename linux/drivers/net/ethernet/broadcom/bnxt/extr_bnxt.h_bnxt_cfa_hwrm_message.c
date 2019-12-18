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
typedef  int u16 ;

/* Variables and functions */
#define  HWRM_CFA_DECAP_FILTER_ALLOC 147 
#define  HWRM_CFA_DECAP_FILTER_FREE 146 
#define  HWRM_CFA_EM_FLOW_ALLOC 145 
#define  HWRM_CFA_EM_FLOW_CFG 144 
#define  HWRM_CFA_EM_FLOW_FREE 143 
#define  HWRM_CFA_ENCAP_RECORD_ALLOC 142 
#define  HWRM_CFA_ENCAP_RECORD_FREE 141 
#define  HWRM_CFA_FLOW_ALLOC 140 
#define  HWRM_CFA_FLOW_FLUSH 139 
#define  HWRM_CFA_FLOW_FREE 138 
#define  HWRM_CFA_FLOW_INFO 137 
#define  HWRM_CFA_FLOW_STATS 136 
#define  HWRM_CFA_METER_INSTANCE_ALLOC 135 
#define  HWRM_CFA_METER_INSTANCE_FREE 134 
#define  HWRM_CFA_METER_PROFILE_ALLOC 133 
#define  HWRM_CFA_METER_PROFILE_CFG 132 
#define  HWRM_CFA_METER_PROFILE_FREE 131 
#define  HWRM_CFA_NTUPLE_FILTER_ALLOC 130 
#define  HWRM_CFA_NTUPLE_FILTER_CFG 129 
#define  HWRM_CFA_NTUPLE_FILTER_FREE 128 

__attribute__((used)) static inline bool bnxt_cfa_hwrm_message(u16 req_type)
{
	switch (req_type) {
	case HWRM_CFA_ENCAP_RECORD_ALLOC:
	case HWRM_CFA_ENCAP_RECORD_FREE:
	case HWRM_CFA_DECAP_FILTER_ALLOC:
	case HWRM_CFA_DECAP_FILTER_FREE:
	case HWRM_CFA_NTUPLE_FILTER_ALLOC:
	case HWRM_CFA_NTUPLE_FILTER_FREE:
	case HWRM_CFA_NTUPLE_FILTER_CFG:
	case HWRM_CFA_EM_FLOW_ALLOC:
	case HWRM_CFA_EM_FLOW_FREE:
	case HWRM_CFA_EM_FLOW_CFG:
	case HWRM_CFA_FLOW_ALLOC:
	case HWRM_CFA_FLOW_FREE:
	case HWRM_CFA_FLOW_INFO:
	case HWRM_CFA_FLOW_FLUSH:
	case HWRM_CFA_FLOW_STATS:
	case HWRM_CFA_METER_PROFILE_ALLOC:
	case HWRM_CFA_METER_PROFILE_FREE:
	case HWRM_CFA_METER_PROFILE_CFG:
	case HWRM_CFA_METER_INSTANCE_ALLOC:
	case HWRM_CFA_METER_INSTANCE_FREE:
		return true;
	default:
		return false;
	}
}