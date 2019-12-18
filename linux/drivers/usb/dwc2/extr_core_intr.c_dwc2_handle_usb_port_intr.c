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
struct dwc2_hsotg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPRT0 ; 
 int HPRT0_ENA ; 
 int HPRT0_ENACHG ; 
 int dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dwc2_handle_usb_port_intr(struct dwc2_hsotg *hsotg)
{
	u32 hprt0 = dwc2_readl(hsotg, HPRT0);

	if (hprt0 & HPRT0_ENACHG) {
		hprt0 &= ~HPRT0_ENA;
		dwc2_writel(hsotg, hprt0, HPRT0);
	}
}