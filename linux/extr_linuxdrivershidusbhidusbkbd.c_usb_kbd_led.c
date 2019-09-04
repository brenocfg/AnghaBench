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
struct usb_kbd {scalar_t__* leds; scalar_t__ newleds; int led_urb_submitted; int /*<<< orphan*/  leds_lock; TYPE_1__* led; int /*<<< orphan*/  usbdev; } ;
struct urb {int /*<<< orphan*/  dev; scalar_t__ status; struct usb_kbd* context; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  hid_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hid_warn (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ usb_submit_urb (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usb_kbd_led(struct urb *urb)
{
	unsigned long flags;
	struct usb_kbd *kbd = urb->context;

	if (urb->status)
		hid_warn(urb->dev, "led urb status %d received\n",
			 urb->status);

	spin_lock_irqsave(&kbd->leds_lock, flags);

	if (*(kbd->leds) == kbd->newleds){
		kbd->led_urb_submitted = false;
		spin_unlock_irqrestore(&kbd->leds_lock, flags);
		return;
	}

	*(kbd->leds) = kbd->newleds;
	
	kbd->led->dev = kbd->usbdev;
	if (usb_submit_urb(kbd->led, GFP_ATOMIC)){
		hid_err(urb->dev, "usb_submit_urb(leds) failed\n");
		kbd->led_urb_submitted = false;
	}
	spin_unlock_irqrestore(&kbd->leds_lock, flags);
	
}