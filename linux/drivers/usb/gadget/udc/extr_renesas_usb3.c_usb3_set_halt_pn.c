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
struct renesas_usb3_ep {int halt; int /*<<< orphan*/  wedge; int /*<<< orphan*/  num; } ;
struct renesas_usb3 {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  PN_CON_EN ; 
 int /*<<< orphan*/  USB3_PN_CON ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct renesas_usb3* usb3_ep_to_usb3 (struct renesas_usb3_ep*) ; 
 int /*<<< orphan*/  usb3_pn_change (struct renesas_usb3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb3_pn_con_clear (struct renesas_usb3*) ; 
 int /*<<< orphan*/  usb3_pn_stall (struct renesas_usb3*) ; 
 int /*<<< orphan*/  usb3_pn_stop (struct renesas_usb3*) ; 
 int /*<<< orphan*/  usb3_set_bit (struct renesas_usb3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usb3_set_halt_pn(struct renesas_usb3_ep *usb3_ep, bool halt,
			    bool is_clear_feature)
{
	struct renesas_usb3 *usb3 = usb3_ep_to_usb3(usb3_ep);
	unsigned long flags;

	spin_lock_irqsave(&usb3->lock, flags);
	if (!usb3_pn_change(usb3, usb3_ep->num)) {
		usb3_ep->halt = halt;
		if (halt) {
			usb3_pn_stall(usb3);
		} else if (!is_clear_feature || !usb3_ep->wedge) {
			usb3_pn_con_clear(usb3);
			usb3_set_bit(usb3, PN_CON_EN, USB3_PN_CON);
			usb3_pn_stop(usb3);
		}
	}
	spin_unlock_irqrestore(&usb3->lock, flags);

	return 0;
}