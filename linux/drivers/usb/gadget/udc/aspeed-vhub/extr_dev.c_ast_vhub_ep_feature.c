#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_4__ {int is_in; int stalled; scalar_t__ is_iso; int /*<<< orphan*/  enabled; } ;
struct TYPE_3__ {int /*<<< orphan*/  desc; } ;
struct ast_vhub_ep {TYPE_2__ epn; TYPE_1__ ep; } ;
struct ast_vhub_dev {struct ast_vhub_ep** epns; } ;

/* Variables and functions */
 int AST_VHUB_NUM_GEN_EPs ; 
 int /*<<< orphan*/  DDBG (struct ast_vhub_dev*,char*,char*,int,...) ; 
 int USB_DIR_IN ; 
 int USB_ENDPOINT_HALT ; 
 int USB_ENDPOINT_NUMBER_MASK ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  ast_vhub_update_epn_stall (struct ast_vhub_ep*) ; 
 int std_req_complete ; 
 int std_req_driver ; 
 int std_req_stall ; 

__attribute__((used)) static int ast_vhub_ep_feature(struct ast_vhub_dev *d,
			       u16 wIndex, u16 wValue, bool is_set)
{
	struct ast_vhub_ep *ep;
	int ep_num;

	ep_num = wIndex & USB_ENDPOINT_NUMBER_MASK;
	DDBG(d, "%s_FEATURE(ep%d val=%02x)\n",
	     is_set ? "SET" : "CLEAR", ep_num, wValue);
	if (ep_num == 0)
		return std_req_complete;
	if (ep_num >= AST_VHUB_NUM_GEN_EPs || !d->epns[ep_num - 1])
		return std_req_stall;
	if (wValue != USB_ENDPOINT_HALT)
		return std_req_driver;

	ep = d->epns[ep_num - 1];
	if (WARN_ON(!ep))
		return std_req_stall;

	if (!ep->epn.enabled || !ep->ep.desc || ep->epn.is_iso ||
	    ep->epn.is_in != !!(wIndex & USB_DIR_IN))
		return std_req_stall;

	DDBG(d, "%s stall on EP %d\n",
	     is_set ? "setting" : "clearing", ep_num);
	ep->epn.stalled = is_set;
	ast_vhub_update_epn_stall(ep);

	return std_req_complete;
}