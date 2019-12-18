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
struct renesas_usb3 {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int AXI_INT_DMAINT ; 
 int AXI_INT_EPCINT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  USB3_AXI_INT_STA ; 
 int /*<<< orphan*/  usb3_irq_dma (struct renesas_usb3*) ; 
 int /*<<< orphan*/  usb3_irq_epc (struct renesas_usb3*) ; 
 int usb3_read (struct renesas_usb3*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t renesas_usb3_irq(int irq, void *_usb3)
{
	struct renesas_usb3 *usb3 = _usb3;
	irqreturn_t ret = IRQ_NONE;
	u32 axi_int_sta = usb3_read(usb3, USB3_AXI_INT_STA);

	if (axi_int_sta & AXI_INT_DMAINT) {
		usb3_irq_dma(usb3);
		ret = IRQ_HANDLED;
	}

	if (axi_int_sta & AXI_INT_EPCINT) {
		usb3_irq_epc(usb3);
		ret = IRQ_HANDLED;
	}

	return ret;
}