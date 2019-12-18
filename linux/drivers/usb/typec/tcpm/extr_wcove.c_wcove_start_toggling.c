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
struct wcove_typec {int /*<<< orphan*/  regmap; } ;
struct tcpc_dev {int dummy; } ;
typedef  enum typec_port_type { ____Placeholder_typec_port_type } typec_port_type ;
typedef  enum typec_cc_status { ____Placeholder_typec_cc_status } typec_cc_status ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  TYPEC_CC_RP_1_5 129 
#define  TYPEC_CC_RP_3_0 128 
 int TYPEC_PORT_DRP ; 
 int /*<<< orphan*/  USBC_CONTROL1 ; 
 unsigned int USBC_CONTROL1_CURSRC_UA_180 ; 
 unsigned int USBC_CONTROL1_CURSRC_UA_330 ; 
 unsigned int USBC_CONTROL1_CURSRC_UA_80 ; 
 unsigned int USBC_CONTROL1_DRPTOGGLE_RANDOM ; 
 unsigned int USBC_CONTROL1_MODE_DRP ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct wcove_typec* tcpc_to_wcove (struct tcpc_dev*) ; 

__attribute__((used)) static int wcove_start_toggling(struct tcpc_dev *tcpc,
				enum typec_port_type port_type,
				enum typec_cc_status cc)
{
	struct wcove_typec *wcove = tcpc_to_wcove(tcpc);
	unsigned int usbc_ctrl;

	if (port_type != TYPEC_PORT_DRP)
		return -EOPNOTSUPP;

	usbc_ctrl = USBC_CONTROL1_MODE_DRP | USBC_CONTROL1_DRPTOGGLE_RANDOM;

	switch (cc) {
	case TYPEC_CC_RP_1_5:
		usbc_ctrl |= USBC_CONTROL1_CURSRC_UA_180;
		break;
	case TYPEC_CC_RP_3_0:
		usbc_ctrl |= USBC_CONTROL1_CURSRC_UA_330;
		break;
	default:
		usbc_ctrl |= USBC_CONTROL1_CURSRC_UA_80;
		break;
	}

	return regmap_write(wcove->regmap, USBC_CONTROL1, usbc_ctrl);
}