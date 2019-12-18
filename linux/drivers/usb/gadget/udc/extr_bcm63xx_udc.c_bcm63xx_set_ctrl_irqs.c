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
struct bcm63xx_udc {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_EVENT_IRQ_MASK_REG ; 
 int /*<<< orphan*/  USBD_EVENT_IRQ_SETCFG ; 
 int /*<<< orphan*/  USBD_EVENT_IRQ_SETINTF ; 
 int /*<<< orphan*/  USBD_EVENT_IRQ_SETUP ; 
 int /*<<< orphan*/  USBD_EVENT_IRQ_STATUS_REG ; 
 int /*<<< orphan*/  USBD_EVENT_IRQ_USB_LINK ; 
 int /*<<< orphan*/  USBD_EVENT_IRQ_USB_RESET ; 
 int /*<<< orphan*/  USBD_STATUS_REG ; 
 int /*<<< orphan*/  usbd_writel (struct bcm63xx_udc*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm63xx_set_ctrl_irqs(struct bcm63xx_udc *udc, bool enable_irqs)
{
	u32 val;

	usbd_writel(udc, 0, USBD_STATUS_REG);

	val = BIT(USBD_EVENT_IRQ_USB_RESET) |
	      BIT(USBD_EVENT_IRQ_SETUP) |
	      BIT(USBD_EVENT_IRQ_SETCFG) |
	      BIT(USBD_EVENT_IRQ_SETINTF) |
	      BIT(USBD_EVENT_IRQ_USB_LINK);
	usbd_writel(udc, enable_irqs ? val : 0, USBD_EVENT_IRQ_MASK_REG);
	usbd_writel(udc, val, USBD_EVENT_IRQ_STATUS_REG);
}