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
typedef  int /*<<< orphan*/  u8 ;
struct nic78bx_led {TYPE_1__* data; int /*<<< orphan*/  bit; int /*<<< orphan*/  mask; } ;
struct led_classdev {int dummy; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  io_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct nic78bx_led* to_nic78bx_led (struct led_classdev*) ; 

__attribute__((used)) static void nic78bx_brightness_set(struct led_classdev *cdev,
				  enum led_brightness brightness)
{
	struct nic78bx_led *nled = to_nic78bx_led(cdev);
	unsigned long flags;
	u8 value;

	spin_lock_irqsave(&nled->data->lock, flags);
	value = inb(nled->data->io_base);

	if (brightness) {
		value &= ~nled->mask;
		value |= nled->bit;
	} else {
		value &= ~nled->bit;
	}

	outb(value, nled->data->io_base);
	spin_unlock_irqrestore(&nled->data->lock, flags);
}