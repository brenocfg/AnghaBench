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
typedef  int u16 ;
struct gpio_chip {unsigned int ngpio; } ;

/* Variables and functions */
 int GIUPIODH ; 
 int GIUPIODL ; 
 int GIUPODATH ; 
 int GIUPODATL ; 
 int /*<<< orphan*/  giu_lock ; 
 int giu_read (int) ; 
 int /*<<< orphan*/  giu_write (int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void vr41xx_gpio_set(struct gpio_chip *chip, unsigned pin,
			    int value)
{
	u16 offset, mask, reg;
	unsigned long flags;

	if (pin >= chip->ngpio)
		return;

	if (pin < 16) {
		offset = GIUPIODL;
		mask = 1 << pin;
	} else if (pin < 32) {
		offset = GIUPIODH;
		mask = 1 << (pin - 16);
	} else if (pin < 48) {
		offset = GIUPODATL;
		mask = 1 << (pin - 32);
	} else {
		offset = GIUPODATH;
		mask = 1 << (pin - 48);
	}

	spin_lock_irqsave(&giu_lock, flags);

	reg = giu_read(offset);
	if (value)
		reg |= mask;
	else
		reg &= ~mask;
	giu_write(offset, reg);

	spin_unlock_irqrestore(&giu_lock, flags);
}