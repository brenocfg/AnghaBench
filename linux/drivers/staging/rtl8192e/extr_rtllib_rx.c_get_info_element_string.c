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
#define  MFIE_TYPE_CF_SET 153 
#define  MFIE_TYPE_CHALLENGE 152 
#define  MFIE_TYPE_COUNTRY 151 
#define  MFIE_TYPE_CSA 150 
#define  MFIE_TYPE_DS_SET 149 
#define  MFIE_TYPE_FH_SET 148 
#define  MFIE_TYPE_GENERIC 147 
#define  MFIE_TYPE_HOP_PARAMS 146 
#define  MFIE_TYPE_HOP_TABLE 145 
#define  MFIE_TYPE_IBSS_DFS 144 
#define  MFIE_TYPE_IBSS_SET 143 
#define  MFIE_TYPE_MEASURE_REPORT 142 
#define  MFIE_TYPE_MEASURE_REQUEST 141 
#define  MFIE_TYPE_POWER_CAPABILITY 140 
#define  MFIE_TYPE_POWER_CONSTRAINT 139 
#define  MFIE_TYPE_QOS_PARAMETER 138 
#define  MFIE_TYPE_QUIET 137 
#define  MFIE_TYPE_RATES 136 
#define  MFIE_TYPE_RATES_EX 135 
#define  MFIE_TYPE_REQUEST 134 
#define  MFIE_TYPE_RSN 133 
#define  MFIE_TYPE_SSID 132 
#define  MFIE_TYPE_SUPP_CHANNELS 131 
#define  MFIE_TYPE_TIM 130 
#define  MFIE_TYPE_TPC_REPORT 129 
#define  MFIE_TYPE_TPC_REQUEST 128 

__attribute__((used)) static const char *get_info_element_string(u16 id)
{
	switch (id) {
	case MFIE_TYPE_SSID:
		return "SSID";
	case MFIE_TYPE_RATES:
		return "RATES";
	case MFIE_TYPE_FH_SET:
		return "FH_SET";
	case MFIE_TYPE_DS_SET:
		return "DS_SET";
	case MFIE_TYPE_CF_SET:
		return "CF_SET";
	case MFIE_TYPE_TIM:
		return "TIM";
	case MFIE_TYPE_IBSS_SET:
		return "IBSS_SET";
	case MFIE_TYPE_COUNTRY:
		return "COUNTRY";
	case MFIE_TYPE_HOP_PARAMS:
		return "HOP_PARAMS";
	case MFIE_TYPE_HOP_TABLE:
		return "HOP_TABLE";
	case MFIE_TYPE_REQUEST:
		return "REQUEST";
	case MFIE_TYPE_CHALLENGE:
		return "CHALLENGE";
	case MFIE_TYPE_POWER_CONSTRAINT:
		return "POWER_CONSTRAINT";
	case MFIE_TYPE_POWER_CAPABILITY:
		return "POWER_CAPABILITY";
	case MFIE_TYPE_TPC_REQUEST:
		return "TPC_REQUEST";
	case MFIE_TYPE_TPC_REPORT:
		return "TPC_REPORT";
	case MFIE_TYPE_SUPP_CHANNELS:
		return "SUPP_CHANNELS";
	case MFIE_TYPE_CSA:
		return "CSA";
	case MFIE_TYPE_MEASURE_REQUEST:
		return "MEASURE_REQUEST";
	case MFIE_TYPE_MEASURE_REPORT:
		return "MEASURE_REPORT";
	case MFIE_TYPE_QUIET:
		return "QUIET";
	case MFIE_TYPE_IBSS_DFS:
		return "IBSS_DFS";
	case MFIE_TYPE_RSN:
		return "RSN";
	case MFIE_TYPE_RATES_EX:
		return "RATES_EX";
	case MFIE_TYPE_GENERIC:
		return "GENERIC";
	case MFIE_TYPE_QOS_PARAMETER:
		return "QOS_PARAMETER";
	default:
		return "UNKNOWN";
	}
}