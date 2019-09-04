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
typedef  int u32 ;
struct ks8695_priv {scalar_t__ phyiface_regs; } ;

/* Variables and functions */
 scalar_t__ KS8695_PPS ; 
 scalar_t__ KS8695_WMC ; 
 scalar_t__ KS8695_WPPM ; 
 int WLED0S_ACTIVITY ; 
 int WLED1S_LINK ; 
 int WMC_WANA100F ; 
 int WMC_WANA100H ; 
 int WMC_WANA10F ; 
 int WMC_WANA10H ; 
 int WMC_WANAP ; 
 int WMC_WANR ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void
ks8695_init_wan_phy(struct ks8695_priv *ksp)
{
	u32 ctrl;

	/* Support auto-negotiation */
	ctrl = (WMC_WANAP | WMC_WANA100F | WMC_WANA100H |
		WMC_WANA10F | WMC_WANA10H);

	/* LED0 = Activity , LED1 = Link */
	ctrl |= (WLED0S_ACTIVITY | WLED1S_LINK);

	/* Restart Auto-negotiation */
	ctrl |= WMC_WANR;

	writel(ctrl, ksp->phyiface_regs + KS8695_WMC);

	writel(0, ksp->phyiface_regs + KS8695_WPPM);
	writel(0, ksp->phyiface_regs + KS8695_PPS);
}