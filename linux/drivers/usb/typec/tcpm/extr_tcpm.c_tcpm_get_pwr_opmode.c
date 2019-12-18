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
typedef  enum typec_pwr_opmode { ____Placeholder_typec_pwr_opmode } typec_pwr_opmode ;
typedef  enum typec_cc_status { ____Placeholder_typec_cc_status } typec_cc_status ;

/* Variables and functions */
#define  TYPEC_CC_RP_1_5 130 
#define  TYPEC_CC_RP_3_0 129 
#define  TYPEC_CC_RP_DEF 128 
 int TYPEC_PWR_MODE_1_5A ; 
 int TYPEC_PWR_MODE_3_0A ; 
 int TYPEC_PWR_MODE_USB ; 

__attribute__((used)) static enum typec_pwr_opmode tcpm_get_pwr_opmode(enum typec_cc_status cc)
{
	switch (cc) {
	case TYPEC_CC_RP_1_5:
		return TYPEC_PWR_MODE_1_5A;
	case TYPEC_CC_RP_3_0:
		return TYPEC_PWR_MODE_3_0A;
	case TYPEC_CC_RP_DEF:
	default:
		return TYPEC_PWR_MODE_USB;
	}
}