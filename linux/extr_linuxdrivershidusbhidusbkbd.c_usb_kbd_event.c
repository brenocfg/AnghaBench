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
struct usb_kbd {int newleds; int led_urb_submitted; int* leds; int /*<<< orphan*/  leds_lock; TYPE_1__* led; int /*<<< orphan*/  usbdev; } ;
struct input_dev {int /*<<< orphan*/  led; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int EV_LED ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  LED_CAPSL ; 
 int /*<<< orphan*/  LED_COMPOSE ; 
 int /*<<< orphan*/  LED_KANA ; 
 int /*<<< orphan*/  LED_NUML ; 
 int /*<<< orphan*/  LED_SCROLLL ; 
 struct usb_kbd* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_submit_urb (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usb_kbd_event(struct input_dev *dev, unsigned int type,
			 unsigned int code, int value)
{
	unsigned long flags;
	struct usb_kbd *kbd = input_get_drvdata(dev);

	if (type != EV_LED)
		return -1;

	spin_lock_irqsave(&kbd->leds_lock, flags);
	kbd->newleds = (!!test_bit(LED_KANA,    dev->led) << 3) | (!!test_bit(LED_COMPOSE, dev->led) << 3) |
		       (!!test_bit(LED_SCROLLL, dev->led) << 2) | (!!test_bit(LED_CAPSL,   dev->led) << 1) |
		       (!!test_bit(LED_NUML,    dev->led));

	if (kbd->led_urb_submitted){
		spin_unlock_irqrestore(&kbd->leds_lock, flags);
		return 0;
	}

	if (*(kbd->leds) == kbd->newleds){
		spin_unlock_irqrestore(&kbd->leds_lock, flags);
		return 0;
	}

	*(kbd->leds) = kbd->newleds;
	
	kbd->led->dev = kbd->usbdev;
	if (usb_submit_urb(kbd->led, GFP_ATOMIC))
		pr_err("usb_submit_urb(leds) failed\n");
	else
		kbd->led_urb_submitted = true;
	
	spin_unlock_irqrestore(&kbd->leds_lock, flags);
	
	return 0;
}