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
struct usb_hub {int dummy; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 struct usb_hub* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct usb_hub* hub ; 
 int /*<<< orphan*/  hub_resubmit_irq_urb (struct usb_hub*) ; 
 int /*<<< orphan*/  irq_urb_retry ; 

__attribute__((used)) static void hub_retry_irq_urb(struct timer_list *t)
{
	struct usb_hub *hub = from_timer(hub, t, irq_urb_retry);

	hub_resubmit_irq_urb(hub);
}