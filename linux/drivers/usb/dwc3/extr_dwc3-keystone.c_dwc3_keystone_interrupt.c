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
struct dwc3_keystone {int /*<<< orphan*/  usbss; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  USBSS_IRQENABLE_CLR_0 ; 
 int /*<<< orphan*/  USBSS_IRQENABLE_SET_0 ; 
 int /*<<< orphan*/  USBSS_IRQSTATUS_0 ; 
 int /*<<< orphan*/  USBSS_IRQ_COREIRQ_CLR ; 
 int /*<<< orphan*/  USBSS_IRQ_COREIRQ_EN ; 
 int /*<<< orphan*/  USBSS_IRQ_EOI ; 
 int /*<<< orphan*/  USBSS_IRQ_EOI_LINE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBSS_IRQ_EVENT_ST ; 
 int /*<<< orphan*/  kdwc3_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t dwc3_keystone_interrupt(int irq, void *_kdwc)
{
	struct dwc3_keystone	*kdwc = _kdwc;

	kdwc3_writel(kdwc->usbss, USBSS_IRQENABLE_CLR_0, USBSS_IRQ_COREIRQ_CLR);
	kdwc3_writel(kdwc->usbss, USBSS_IRQSTATUS_0, USBSS_IRQ_EVENT_ST);
	kdwc3_writel(kdwc->usbss, USBSS_IRQENABLE_SET_0, USBSS_IRQ_COREIRQ_EN);
	kdwc3_writel(kdwc->usbss, USBSS_IRQ_EOI, USBSS_IRQ_EOI_LINE(0));

	return IRQ_HANDLED;
}