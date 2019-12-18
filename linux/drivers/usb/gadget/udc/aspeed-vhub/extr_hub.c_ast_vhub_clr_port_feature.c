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
typedef  size_t u8 ;
typedef  int u16 ;
struct ast_vhub_port {int status; unsigned int change; int /*<<< orphan*/  dev; } ;
struct ast_vhub_ep {struct ast_vhub* vhub; } ;
struct ast_vhub {struct ast_vhub_port* ports; } ;
typedef  enum std_req_rc { ____Placeholder_std_req_rc } std_req_rc ;

/* Variables and functions */
 size_t AST_VHUB_NUM_PORTS ; 
#define  USB_PORT_FEAT_C_CONNECTION 136 
#define  USB_PORT_FEAT_C_ENABLE 135 
#define  USB_PORT_FEAT_C_OVER_CURRENT 134 
#define  USB_PORT_FEAT_C_RESET 133 
#define  USB_PORT_FEAT_C_SUSPEND 132 
#define  USB_PORT_FEAT_ENABLE 131 
#define  USB_PORT_FEAT_INDICATOR 130 
#define  USB_PORT_FEAT_POWER 129 
#define  USB_PORT_FEAT_SUSPEND 128 
 int USB_PORT_STAT_ENABLE ; 
 int USB_PORT_STAT_SUSPEND ; 
 int /*<<< orphan*/  ast_vhub_change_port_stat (struct ast_vhub*,size_t,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ast_vhub_dev_resume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ast_vhub_dev_suspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ast_vhub_update_hub_ep1 (struct ast_vhub*,size_t) ; 
 int std_req_complete ; 
 int std_req_stall ; 

__attribute__((used)) static enum std_req_rc ast_vhub_clr_port_feature(struct ast_vhub_ep *ep,
						 u8 port, u16 feat)
{
	struct ast_vhub *vhub = ep->vhub;
	struct ast_vhub_port *p;

	if (port == 0 || port > AST_VHUB_NUM_PORTS)
		return std_req_stall;
	port--;
	p = &vhub->ports[port];

	switch(feat) {
	case USB_PORT_FEAT_ENABLE:
		ast_vhub_change_port_stat(vhub, port,
					  USB_PORT_STAT_ENABLE |
					  USB_PORT_STAT_SUSPEND, 0,
					  false);
		ast_vhub_dev_suspend(&p->dev);
		return std_req_complete;
	case USB_PORT_FEAT_SUSPEND:
		if (!(p->status & USB_PORT_STAT_SUSPEND))
			return std_req_complete;
		ast_vhub_change_port_stat(vhub, port,
					  USB_PORT_STAT_SUSPEND, 0,
					  false);
		ast_vhub_dev_resume(&p->dev);
		return std_req_complete;
	case USB_PORT_FEAT_POWER:
		/* We don't do power control */
		return std_req_complete;
	case USB_PORT_FEAT_INDICATOR:
		/* We don't have indicators */
		return std_req_complete;
	case USB_PORT_FEAT_C_CONNECTION:
	case USB_PORT_FEAT_C_ENABLE:
	case USB_PORT_FEAT_C_SUSPEND:
	case USB_PORT_FEAT_C_OVER_CURRENT:
	case USB_PORT_FEAT_C_RESET:
		/* Clear state-change feature */
		p->change &= ~(1u << (feat - 16));
		ast_vhub_update_hub_ep1(vhub, port);
		return std_req_complete;
	}
	return std_req_stall;
}