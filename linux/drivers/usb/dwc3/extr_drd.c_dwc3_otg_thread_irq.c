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
struct dwc3 {int /*<<< orphan*/  lock; scalar_t__ otg_restart_host; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_GCTL_PRTCAP_OTG ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dwc3_otg_host_init (struct dwc3*) ; 
 int /*<<< orphan*/  dwc3_set_mode (struct dwc3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t dwc3_otg_thread_irq(int irq, void *_dwc)
{
	struct dwc3 *dwc = _dwc;

	spin_lock(&dwc->lock);
	if (dwc->otg_restart_host) {
		dwc3_otg_host_init(dwc);
		dwc->otg_restart_host = 0;
	}

	spin_unlock(&dwc->lock);

	dwc3_set_mode(dwc, DWC3_GCTL_PRTCAP_OTG);

	return IRQ_HANDLED;
}