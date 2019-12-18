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

/* Variables and functions */
#define  SCU_EVENT_HARD_RESET_RECEIVED 148 
#define  SCU_EVENT_HARD_RESET_TRANSMITTED 147 
#define  SCU_EVENT_LINK_FAILURE 146 
#define  SCU_EVENT_PORT_SELECTOR_DETECTED 145 
#define  SCU_EVENT_RECEIVED_IDENTIFY_TIMEOUT 144 
#define  SCU_EVENT_SAS_15 143 
#define  SCU_EVENT_SAS_15_SSC 142 
#define  SCU_EVENT_SAS_30 141 
#define  SCU_EVENT_SAS_30_SSC 140 
#define  SCU_EVENT_SAS_60 139 
#define  SCU_EVENT_SAS_60_SSC 138 
#define  SCU_EVENT_SAS_PHY_DETECTED 137 
#define  SCU_EVENT_SATA_15 136 
#define  SCU_EVENT_SATA_15_SSC 135 
#define  SCU_EVENT_SATA_30 134 
#define  SCU_EVENT_SATA_30_SSC 133 
#define  SCU_EVENT_SATA_60 132 
#define  SCU_EVENT_SATA_60_SSC 131 
#define  SCU_EVENT_SATA_PHY_DETECTED 130 
#define  SCU_EVENT_SATA_SPINUP_HOLD 129 
#define  SCU_EVENT_SENT_PORT_SELECTION 128 
 int scu_get_event_code (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *phy_event_name(u32 event_code)
{
	switch (scu_get_event_code(event_code)) {
	case SCU_EVENT_PORT_SELECTOR_DETECTED:
		return "port selector";
	case SCU_EVENT_SENT_PORT_SELECTION:
		return "port selection";
	case SCU_EVENT_HARD_RESET_TRANSMITTED:
		return "tx hard reset";
	case SCU_EVENT_HARD_RESET_RECEIVED:
		return "rx hard reset";
	case SCU_EVENT_RECEIVED_IDENTIFY_TIMEOUT:
		return "identify timeout";
	case SCU_EVENT_LINK_FAILURE:
		return "link fail";
	case SCU_EVENT_SATA_SPINUP_HOLD:
		return "sata spinup hold";
	case SCU_EVENT_SAS_15_SSC:
	case SCU_EVENT_SAS_15:
		return "sas 1.5";
	case SCU_EVENT_SAS_30_SSC:
	case SCU_EVENT_SAS_30:
		return "sas 3.0";
	case SCU_EVENT_SAS_60_SSC:
	case SCU_EVENT_SAS_60:
		return "sas 6.0";
	case SCU_EVENT_SATA_15_SSC:
	case SCU_EVENT_SATA_15:
		return "sata 1.5";
	case SCU_EVENT_SATA_30_SSC:
	case SCU_EVENT_SATA_30:
		return "sata 3.0";
	case SCU_EVENT_SATA_60_SSC:
	case SCU_EVENT_SATA_60:
		return "sata 6.0";
	case SCU_EVENT_SAS_PHY_DETECTED:
		return "sas detect";
	case SCU_EVENT_SATA_PHY_DETECTED:
		return "sata detect";
	default:
		return "unknown";
	}
}