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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct ast_vhub_ep {TYPE_1__* vhub; } ;
struct TYPE_2__ {int ep1_stalled; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ AST_VHUB_EP1_CTRL ; 
 int /*<<< orphan*/  EPDBG (struct ast_vhub_ep*,char*,char*,...) ; 
 int USB_ENDPOINT_HALT ; 
 int USB_ENDPOINT_NUMBER_MASK ; 
 int /*<<< orphan*/  VHUB_EP1_CTRL_RESET_TOGGLE ; 
 int /*<<< orphan*/  VHUB_EP1_CTRL_STALL ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int std_req_complete ; 
 int std_req_stall ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ast_vhub_hub_ep_feature(struct ast_vhub_ep *ep,
				   u16 wIndex, u16 wValue,
				   bool is_set)
{
	int ep_num;
	u32 reg;

	ep_num = wIndex & USB_ENDPOINT_NUMBER_MASK;
	EPDBG(ep, "%s_FEATURE(ep%d val=%02x)\n",
	      is_set ? "SET" : "CLEAR", ep_num, wValue);

	if (ep_num > 1)
		return std_req_stall;
	if (wValue != USB_ENDPOINT_HALT)
		return std_req_stall;
	if (ep_num == 0)
		return std_req_complete;

	EPDBG(ep, "%s stall on EP 1\n",
	      is_set ? "setting" : "clearing");

	ep->vhub->ep1_stalled = is_set;
	reg = readl(ep->vhub->regs + AST_VHUB_EP1_CTRL);
	if (is_set) {
		reg |= VHUB_EP1_CTRL_STALL;
	} else {
		reg &= ~VHUB_EP1_CTRL_STALL;
		reg |= VHUB_EP1_CTRL_RESET_TOGGLE;
	}
	writel(reg, ep->vhub->regs + AST_VHUB_EP1_CTRL);

	return std_req_complete;
}