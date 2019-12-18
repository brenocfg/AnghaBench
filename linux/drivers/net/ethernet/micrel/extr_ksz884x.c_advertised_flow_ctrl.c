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
typedef  int /*<<< orphan*/  u16 ;
struct ksz_port {int flow_ctrl; } ;

/* Variables and functions */
#define  PHY_FLOW_CTRL 130 
#define  PHY_RX_ONLY 129 
#define  PHY_TX_ONLY 128 
 int /*<<< orphan*/  PORT_AUTO_NEG_SYM_PAUSE ; 

__attribute__((used)) static u16 advertised_flow_ctrl(struct ksz_port *port, u16 ctrl)
{
	ctrl &= ~PORT_AUTO_NEG_SYM_PAUSE;
	switch (port->flow_ctrl) {
	case PHY_FLOW_CTRL:
		ctrl |= PORT_AUTO_NEG_SYM_PAUSE;
		break;
	/* Not supported. */
	case PHY_TX_ONLY:
	case PHY_RX_ONLY:
	default:
		break;
	}
	return ctrl;
}