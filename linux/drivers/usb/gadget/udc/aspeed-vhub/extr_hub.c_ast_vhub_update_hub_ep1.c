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
struct ast_vhub {scalar_t__ regs; TYPE_1__* ports; } ;
struct TYPE_2__ {scalar_t__ change; } ;

/* Variables and functions */
 scalar_t__ AST_VHUB_EP1_STS_CHG ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void ast_vhub_update_hub_ep1(struct ast_vhub *vhub,
				    unsigned int port)
{
	/* Update HW EP1 response */
	u32 reg = readl(vhub->regs + AST_VHUB_EP1_STS_CHG);
	u32 pmask = (1 << (port + 1));
	if (vhub->ports[port].change)
		reg |= pmask;
	else
		reg &= ~pmask;
	writel(reg, vhub->regs + AST_VHUB_EP1_STS_CHG);
}