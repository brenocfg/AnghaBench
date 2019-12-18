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
struct TYPE_2__ {int /*<<< orphan*/  power_down; } ;
struct dwc2_hsotg {int bus_suspended; int /*<<< orphan*/  lock; TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPRT0 ; 
 int HPRT0_RES ; 
 int HPRT0_SUSP ; 
 int /*<<< orphan*/  PCGCTL ; 
 int PCGCTL_STOPPCLK ; 
 int USB_RESUME_TIMEOUT ; 
 int dwc2_read_hprt0 (struct dwc2_hsotg*) ; 
 int dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void dwc2_port_resume(struct dwc2_hsotg *hsotg)
{
	unsigned long flags;
	u32 hprt0;
	u32 pcgctl;

	spin_lock_irqsave(&hsotg->lock, flags);

	/*
	 * If power_down is supported, Phy clock is already resumed
	 * after registers restore.
	 */
	if (!hsotg->params.power_down) {
		pcgctl = dwc2_readl(hsotg, PCGCTL);
		pcgctl &= ~PCGCTL_STOPPCLK;
		dwc2_writel(hsotg, pcgctl, PCGCTL);
		spin_unlock_irqrestore(&hsotg->lock, flags);
		msleep(20);
		spin_lock_irqsave(&hsotg->lock, flags);
	}

	hprt0 = dwc2_read_hprt0(hsotg);
	hprt0 |= HPRT0_RES;
	hprt0 &= ~HPRT0_SUSP;
	dwc2_writel(hsotg, hprt0, HPRT0);
	spin_unlock_irqrestore(&hsotg->lock, flags);

	msleep(USB_RESUME_TIMEOUT);

	spin_lock_irqsave(&hsotg->lock, flags);
	hprt0 = dwc2_read_hprt0(hsotg);
	hprt0 &= ~(HPRT0_RES | HPRT0_SUSP);
	dwc2_writel(hsotg, hprt0, HPRT0);
	hsotg->bus_suspended = false;
	spin_unlock_irqrestore(&hsotg->lock, flags);
}