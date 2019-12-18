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
struct cdns3_device {TYPE_1__* regs; } ;
struct cdns3 {struct cdns3_device* gadget_dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  ep_ien; int /*<<< orphan*/  ep_ists; int /*<<< orphan*/  usb_ien; int /*<<< orphan*/  usb_ists; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t cdns3_device_irq_handler(int irq, void *data)
{
	struct cdns3_device *priv_dev;
	struct cdns3 *cdns = data;
	irqreturn_t ret = IRQ_NONE;
	u32 reg;

	priv_dev = cdns->gadget_dev;

	/* check USB device interrupt */
	reg = readl(&priv_dev->regs->usb_ists);
	if (reg) {
		/* After masking interrupts the new interrupts won't be
		 * reported in usb_ists/ep_ists. In order to not lose some
		 * of them driver disables only detected interrupts.
		 * They will be enabled ASAP after clearing source of
		 * interrupt. This an unusual behavior only applies to
		 * usb_ists register.
		 */
		reg = ~reg & readl(&priv_dev->regs->usb_ien);
		/* mask deferred interrupt. */
		writel(reg, &priv_dev->regs->usb_ien);
		ret = IRQ_WAKE_THREAD;
	}

	/* check endpoint interrupt */
	reg = readl(&priv_dev->regs->ep_ists);
	if (reg) {
		writel(0, &priv_dev->regs->ep_ien);
		ret = IRQ_WAKE_THREAD;
	}

	return ret;
}