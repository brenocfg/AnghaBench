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
typedef  int u8 ;
typedef  int u16 ;
struct b43legacy_wldev {struct b43legacy_wl* wl; } ;
struct b43legacy_wl {int /*<<< orphan*/  leds_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_MMIO_GPIO_CONTROL ; 
 int b43legacy_read16 (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_write16 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void b43legacy_led_turn_off(struct b43legacy_wldev *dev, u8 led_index,
			     bool activelow)
{
	struct b43legacy_wl *wl = dev->wl;
	unsigned long flags;
	u16 ctl;

	spin_lock_irqsave(&wl->leds_lock, flags);
	ctl = b43legacy_read16(dev, B43legacy_MMIO_GPIO_CONTROL);
	if (activelow)
		ctl |= (1 << led_index);
	else
		ctl &= ~(1 << led_index);
	b43legacy_write16(dev, B43legacy_MMIO_GPIO_CONTROL, ctl);
	spin_unlock_irqrestore(&wl->leds_lock, flags);
}