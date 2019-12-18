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
typedef  enum typec_cc_status { ____Placeholder_typec_cc_status } typec_cc_status ;

/* Variables and functions */
 int TYPEC_CC_OPEN ; 
 int TYPEC_CC_RA ; 
 int TYPEC_CC_RD ; 
 int TYPEC_CC_RP_1_5 ; 
 int TYPEC_CC_RP_3_0 ; 
 int TYPEC_CC_RP_DEF ; 
 unsigned int UCSC_CC_STATUS_PWRDEFSNK ; 
 unsigned int UCSC_CC_STATUS_PWR_1P5A_SNK ; 
 unsigned int UCSC_CC_STATUS_PWR_3A_SNK ; 
 int UCSC_CC_STATUS_RX (unsigned int) ; 
 unsigned int UCSC_CC_STATUS_SNK_RP ; 
#define  USBC_CC_STATUS_RA 129 
#define  USBC_CC_STATUS_RD 128 

__attribute__((used)) static enum typec_cc_status wcove_to_typec_cc(unsigned int cc)
{
	if (cc & UCSC_CC_STATUS_SNK_RP) {
		if (cc & UCSC_CC_STATUS_PWRDEFSNK)
			return TYPEC_CC_RP_DEF;
		else if (cc & UCSC_CC_STATUS_PWR_1P5A_SNK)
			return TYPEC_CC_RP_1_5;
		else if (cc & UCSC_CC_STATUS_PWR_3A_SNK)
			return TYPEC_CC_RP_3_0;
	} else {
		switch (UCSC_CC_STATUS_RX(cc)) {
		case USBC_CC_STATUS_RD:
			return TYPEC_CC_RD;
		case USBC_CC_STATUS_RA:
			return TYPEC_CC_RA;
		default:
			break;
		}
	}
	return TYPEC_CC_OPEN;
}