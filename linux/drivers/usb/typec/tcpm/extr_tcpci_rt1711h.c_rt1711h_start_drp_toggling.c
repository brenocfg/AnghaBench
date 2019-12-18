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
struct tcpci_data {int dummy; } ;
struct tcpci {int dummy; } ;
struct rt1711h_chip {int dummy; } ;
typedef  enum typec_cc_status { ____Placeholder_typec_cc_status } typec_cc_status ;

/* Variables and functions */
 int /*<<< orphan*/  TCPC_ROLE_CTRL ; 
 unsigned int TCPC_ROLE_CTRL_CC1_SHIFT ; 
 unsigned int TCPC_ROLE_CTRL_CC2_SHIFT ; 
 unsigned int TCPC_ROLE_CTRL_CC_RD ; 
 unsigned int TCPC_ROLE_CTRL_CC_RP ; 
 unsigned int TCPC_ROLE_CTRL_RP_VAL_1_5 ; 
 unsigned int TCPC_ROLE_CTRL_RP_VAL_3_0 ; 
 unsigned int TCPC_ROLE_CTRL_RP_VAL_DEF ; 
 unsigned int TCPC_ROLE_CTRL_RP_VAL_SHIFT ; 
 int TYPEC_CC_RD ; 
#define  TYPEC_CC_RP_1_5 130 
#define  TYPEC_CC_RP_3_0 129 
#define  TYPEC_CC_RP_DEF 128 
 int rt1711h_write8 (struct rt1711h_chip*,int /*<<< orphan*/ ,unsigned int) ; 
 struct rt1711h_chip* tdata_to_rt1711h (struct tcpci_data*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int rt1711h_start_drp_toggling(struct tcpci *tcpci,
				      struct tcpci_data *tdata,
				      enum typec_cc_status cc)
{
	struct rt1711h_chip *chip = tdata_to_rt1711h(tdata);
	int ret;
	unsigned int reg = 0;

	switch (cc) {
	default:
	case TYPEC_CC_RP_DEF:
		reg |= (TCPC_ROLE_CTRL_RP_VAL_DEF <<
			TCPC_ROLE_CTRL_RP_VAL_SHIFT);
		break;
	case TYPEC_CC_RP_1_5:
		reg |= (TCPC_ROLE_CTRL_RP_VAL_1_5 <<
			TCPC_ROLE_CTRL_RP_VAL_SHIFT);
		break;
	case TYPEC_CC_RP_3_0:
		reg |= (TCPC_ROLE_CTRL_RP_VAL_3_0 <<
			TCPC_ROLE_CTRL_RP_VAL_SHIFT);
		break;
	}

	if (cc == TYPEC_CC_RD)
		reg |= (TCPC_ROLE_CTRL_CC_RD << TCPC_ROLE_CTRL_CC1_SHIFT) |
			   (TCPC_ROLE_CTRL_CC_RD << TCPC_ROLE_CTRL_CC2_SHIFT);
	else
		reg |= (TCPC_ROLE_CTRL_CC_RP << TCPC_ROLE_CTRL_CC1_SHIFT) |
			   (TCPC_ROLE_CTRL_CC_RP << TCPC_ROLE_CTRL_CC2_SHIFT);

	ret = rt1711h_write8(chip, TCPC_ROLE_CTRL, reg);
	if (ret < 0)
		return ret;
	usleep_range(500, 1000);

	return 0;
}