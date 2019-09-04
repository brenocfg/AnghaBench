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
typedef  scalar_t__ irq_level_t ;

/* Variables and functions */
 int /*<<< orphan*/  GIUINTALSELH ; 
 int /*<<< orphan*/  GIUINTALSELL ; 
 int /*<<< orphan*/  GIUINTSTATH ; 
 int /*<<< orphan*/  GIUINTSTATL ; 
 unsigned int GIUINT_HIGH_MAX ; 
 unsigned int GIUINT_HIGH_OFFSET ; 
 scalar_t__ IRQ_LEVEL_HIGH ; 
 int /*<<< orphan*/  giu_clear (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  giu_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  giu_write (int /*<<< orphan*/ ,int) ; 

void vr41xx_set_irq_level(unsigned int pin, irq_level_t level)
{
	u16 mask;

	if (pin < GIUINT_HIGH_OFFSET) {
		mask = 1 << pin;
		if (level == IRQ_LEVEL_HIGH)
			giu_set(GIUINTALSELL, mask);
		else
			giu_clear(GIUINTALSELL, mask);
		giu_write(GIUINTSTATL, mask);
	} else if (pin < GIUINT_HIGH_MAX) {
		mask = 1 << (pin - GIUINT_HIGH_OFFSET);
		if (level == IRQ_LEVEL_HIGH)
			giu_set(GIUINTALSELH, mask);
		else
			giu_clear(GIUINTALSELH, mask);
		giu_write(GIUINTSTATH, mask);
	}
}