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
struct renesas_usb3_ep {int halt; int /*<<< orphan*/  num; } ;
struct renesas_usb3 {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  PN_CON_EN ; 
 int /*<<< orphan*/  USB3_PN_CON ; 
 int /*<<< orphan*/  USB3_PN_INT_ENA ; 
 int /*<<< orphan*/  USB3_PN_RAMMAP ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb3_clear_bit (struct renesas_usb3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct renesas_usb3* usb3_ep_to_usb3 (struct renesas_usb3_ep*) ; 
 int /*<<< orphan*/  usb3_pn_change (struct renesas_usb3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb3_write (struct renesas_usb3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usb3_disable_pipe_n(struct renesas_usb3_ep *usb3_ep)
{
	struct renesas_usb3 *usb3 = usb3_ep_to_usb3(usb3_ep);
	unsigned long flags;

	usb3_ep->halt = false;

	spin_lock_irqsave(&usb3->lock, flags);
	if (!usb3_pn_change(usb3, usb3_ep->num)) {
		usb3_write(usb3, 0, USB3_PN_INT_ENA);
		usb3_write(usb3, 0, USB3_PN_RAMMAP);
		usb3_clear_bit(usb3, PN_CON_EN, USB3_PN_CON);
	}
	spin_unlock_irqrestore(&usb3->lock, flags);

	return 0;
}