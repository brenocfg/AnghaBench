#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tcpm_port {int cc2; int cc1; TYPE_1__* tcpc; scalar_t__ polarity; } ;
typedef  enum typec_cc_status { ____Placeholder_typec_cc_status } typec_cc_status ;
struct TYPE_2__ {int (* get_current_limit ) (TYPE_1__*) ;} ;

/* Variables and functions */
#define  TYPEC_CC_RP_1_5 130 
#define  TYPEC_CC_RP_3_0 129 
#define  TYPEC_CC_RP_DEF 128 
 int stub1 (TYPE_1__*) ; 

__attribute__((used)) static u32 tcpm_get_current_limit(struct tcpm_port *port)
{
	enum typec_cc_status cc;
	u32 limit;

	cc = port->polarity ? port->cc2 : port->cc1;
	switch (cc) {
	case TYPEC_CC_RP_1_5:
		limit = 1500;
		break;
	case TYPEC_CC_RP_3_0:
		limit = 3000;
		break;
	case TYPEC_CC_RP_DEF:
	default:
		if (port->tcpc->get_current_limit)
			limit = port->tcpc->get_current_limit(port->tcpc);
		else
			limit = 0;
		break;
	}

	return limit;
}