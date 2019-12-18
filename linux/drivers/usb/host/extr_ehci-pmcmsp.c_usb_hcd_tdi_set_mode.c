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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct ehci_regs {int dummy; } ;
struct ehci_hcd {struct ehci_regs* regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSP_PIN_USB0_HOST_DEV ; 
 int USB_CTRL_FIFO_THRESH ; 
 int USB_CTRL_MODE_STREAM_DISABLE ; 
 int USB_EHCI_REG_BIT_STAT_STS ; 
 int USB_EHCI_REG_USB_FIFO ; 
 int USB_EHCI_REG_USB_MODE ; 
 int USB_EHCI_REG_USB_STATUS ; 
 int ehci_readl (struct ehci_hcd*,int*) ; 
 int /*<<< orphan*/  ehci_writel (struct ehci_hcd*,int,int*) ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void usb_hcd_tdi_set_mode(struct ehci_hcd *ehci)
{
	u8 *base;
	u8 *statreg;
	u8 *fiforeg;
	u32 val;
	struct ehci_regs *reg_base = ehci->regs;

	/* get register base */
	base = (u8 *)reg_base + USB_EHCI_REG_USB_MODE;
	statreg = (u8 *)reg_base + USB_EHCI_REG_USB_STATUS;
	fiforeg = (u8 *)reg_base + USB_EHCI_REG_USB_FIFO;

	/* Disable controller mode stream */
	val = ehci_readl(ehci, (u32 *)base);
	ehci_writel(ehci, (val | USB_CTRL_MODE_STREAM_DISABLE),
			(u32 *)base);

	/* clear STS to select parallel transceiver interface */
	val = ehci_readl(ehci, (u32 *)statreg);
	val = val & ~USB_EHCI_REG_BIT_STAT_STS;
	ehci_writel(ehci, val, (u32 *)statreg);

	/* write to set the proper fifo threshold */
	ehci_writel(ehci, USB_CTRL_FIFO_THRESH, (u32 *)fiforeg);

	/* set TWI GPIO USB_HOST_DEV pin high */
	gpio_direction_output(MSP_PIN_USB0_HOST_DEV, 1);
}