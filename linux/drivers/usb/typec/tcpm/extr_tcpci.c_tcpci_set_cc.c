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
struct tcpci {int /*<<< orphan*/  regmap; } ;
struct tcpc_dev {int dummy; } ;
typedef  enum typec_cc_status { ____Placeholder_typec_cc_status } typec_cc_status ;

/* Variables and functions */
 int /*<<< orphan*/  TCPC_ROLE_CTRL ; 
 unsigned int TCPC_ROLE_CTRL_CC1_SHIFT ; 
 unsigned int TCPC_ROLE_CTRL_CC2_SHIFT ; 
 unsigned int TCPC_ROLE_CTRL_CC_OPEN ; 
 unsigned int TCPC_ROLE_CTRL_CC_RA ; 
 unsigned int TCPC_ROLE_CTRL_CC_RD ; 
 unsigned int TCPC_ROLE_CTRL_CC_RP ; 
 unsigned int TCPC_ROLE_CTRL_RP_VAL_1_5 ; 
 unsigned int TCPC_ROLE_CTRL_RP_VAL_3_0 ; 
 unsigned int TCPC_ROLE_CTRL_RP_VAL_DEF ; 
 unsigned int TCPC_ROLE_CTRL_RP_VAL_SHIFT ; 
#define  TYPEC_CC_OPEN 133 
#define  TYPEC_CC_RA 132 
#define  TYPEC_CC_RD 131 
#define  TYPEC_CC_RP_1_5 130 
#define  TYPEC_CC_RP_3_0 129 
#define  TYPEC_CC_RP_DEF 128 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct tcpci* tcpc_to_tcpci (struct tcpc_dev*) ; 

__attribute__((used)) static int tcpci_set_cc(struct tcpc_dev *tcpc, enum typec_cc_status cc)
{
	struct tcpci *tcpci = tcpc_to_tcpci(tcpc);
	unsigned int reg;
	int ret;

	switch (cc) {
	case TYPEC_CC_RA:
		reg = (TCPC_ROLE_CTRL_CC_RA << TCPC_ROLE_CTRL_CC1_SHIFT) |
			(TCPC_ROLE_CTRL_CC_RA << TCPC_ROLE_CTRL_CC2_SHIFT);
		break;
	case TYPEC_CC_RD:
		reg = (TCPC_ROLE_CTRL_CC_RD << TCPC_ROLE_CTRL_CC1_SHIFT) |
			(TCPC_ROLE_CTRL_CC_RD << TCPC_ROLE_CTRL_CC2_SHIFT);
		break;
	case TYPEC_CC_RP_DEF:
		reg = (TCPC_ROLE_CTRL_CC_RP << TCPC_ROLE_CTRL_CC1_SHIFT) |
			(TCPC_ROLE_CTRL_CC_RP << TCPC_ROLE_CTRL_CC2_SHIFT) |
			(TCPC_ROLE_CTRL_RP_VAL_DEF <<
			 TCPC_ROLE_CTRL_RP_VAL_SHIFT);
		break;
	case TYPEC_CC_RP_1_5:
		reg = (TCPC_ROLE_CTRL_CC_RP << TCPC_ROLE_CTRL_CC1_SHIFT) |
			(TCPC_ROLE_CTRL_CC_RP << TCPC_ROLE_CTRL_CC2_SHIFT) |
			(TCPC_ROLE_CTRL_RP_VAL_1_5 <<
			 TCPC_ROLE_CTRL_RP_VAL_SHIFT);
		break;
	case TYPEC_CC_RP_3_0:
		reg = (TCPC_ROLE_CTRL_CC_RP << TCPC_ROLE_CTRL_CC1_SHIFT) |
			(TCPC_ROLE_CTRL_CC_RP << TCPC_ROLE_CTRL_CC2_SHIFT) |
			(TCPC_ROLE_CTRL_RP_VAL_3_0 <<
			 TCPC_ROLE_CTRL_RP_VAL_SHIFT);
		break;
	case TYPEC_CC_OPEN:
	default:
		reg = (TCPC_ROLE_CTRL_CC_OPEN << TCPC_ROLE_CTRL_CC1_SHIFT) |
			(TCPC_ROLE_CTRL_CC_OPEN << TCPC_ROLE_CTRL_CC2_SHIFT);
		break;
	}

	ret = regmap_write(tcpci->regmap, TCPC_ROLE_CTRL, reg);
	if (ret < 0)
		return ret;

	return 0;
}