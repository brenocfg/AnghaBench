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
typedef  int irq_trigger_t ;
typedef  scalar_t__ irq_signal_t ;

/* Variables and functions */
 int /*<<< orphan*/  GIUFEDGEINHH ; 
 int /*<<< orphan*/  GIUFEDGEINHL ; 
 int /*<<< orphan*/  GIUINTHTSELH ; 
 int /*<<< orphan*/  GIUINTHTSELL ; 
 int /*<<< orphan*/  GIUINTSTATH ; 
 int /*<<< orphan*/  GIUINTSTATL ; 
 int /*<<< orphan*/  GIUINTTYPH ; 
 int /*<<< orphan*/  GIUINTTYPL ; 
 unsigned int GIUINT_HIGH_MAX ; 
 unsigned int GIUINT_HIGH_OFFSET ; 
 int /*<<< orphan*/  GIUREDGEINHH ; 
 int /*<<< orphan*/  GIUREDGEINHL ; 
 int /*<<< orphan*/  GIU_IRQ (unsigned int) ; 
 int GPIO_HAS_INTERRUPT_EDGE_SELECT ; 
 scalar_t__ IRQ_SIGNAL_HOLD ; 
#define  IRQ_TRIGGER_EDGE_FALLING 129 
#define  IRQ_TRIGGER_EDGE_RISING 128 
 int IRQ_TRIGGER_LEVEL ; 
 int /*<<< orphan*/  giu_clear (int /*<<< orphan*/ ,int) ; 
 int giu_flags ; 
 int /*<<< orphan*/  giu_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  giu_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  giuint_high_irq_chip ; 
 int /*<<< orphan*/  giuint_low_irq_chip ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void vr41xx_set_irq_trigger(unsigned int pin, irq_trigger_t trigger,
			    irq_signal_t signal)
{
	u16 mask;

	if (pin < GIUINT_HIGH_OFFSET) {
		mask = 1 << pin;
		if (trigger != IRQ_TRIGGER_LEVEL) {
			giu_set(GIUINTTYPL, mask);
			if (signal == IRQ_SIGNAL_HOLD)
				giu_set(GIUINTHTSELL, mask);
			else
				giu_clear(GIUINTHTSELL, mask);
			if (giu_flags & GPIO_HAS_INTERRUPT_EDGE_SELECT) {
				switch (trigger) {
				case IRQ_TRIGGER_EDGE_FALLING:
					giu_set(GIUFEDGEINHL, mask);
					giu_clear(GIUREDGEINHL, mask);
					break;
				case IRQ_TRIGGER_EDGE_RISING:
					giu_clear(GIUFEDGEINHL, mask);
					giu_set(GIUREDGEINHL, mask);
					break;
				default:
					giu_set(GIUFEDGEINHL, mask);
					giu_set(GIUREDGEINHL, mask);
					break;
				}
			}
			irq_set_chip_and_handler(GIU_IRQ(pin),
						 &giuint_low_irq_chip,
						 handle_edge_irq);
		} else {
			giu_clear(GIUINTTYPL, mask);
			giu_clear(GIUINTHTSELL, mask);
			irq_set_chip_and_handler(GIU_IRQ(pin),
						 &giuint_low_irq_chip,
						 handle_level_irq);
		}
		giu_write(GIUINTSTATL, mask);
	} else if (pin < GIUINT_HIGH_MAX) {
		mask = 1 << (pin - GIUINT_HIGH_OFFSET);
		if (trigger != IRQ_TRIGGER_LEVEL) {
			giu_set(GIUINTTYPH, mask);
			if (signal == IRQ_SIGNAL_HOLD)
				giu_set(GIUINTHTSELH, mask);
			else
				giu_clear(GIUINTHTSELH, mask);
			if (giu_flags & GPIO_HAS_INTERRUPT_EDGE_SELECT) {
				switch (trigger) {
				case IRQ_TRIGGER_EDGE_FALLING:
					giu_set(GIUFEDGEINHH, mask);
					giu_clear(GIUREDGEINHH, mask);
					break;
				case IRQ_TRIGGER_EDGE_RISING:
					giu_clear(GIUFEDGEINHH, mask);
					giu_set(GIUREDGEINHH, mask);
					break;
				default:
					giu_set(GIUFEDGEINHH, mask);
					giu_set(GIUREDGEINHH, mask);
					break;
				}
			}
			irq_set_chip_and_handler(GIU_IRQ(pin),
						 &giuint_high_irq_chip,
						 handle_edge_irq);
		} else {
			giu_clear(GIUINTTYPH, mask);
			giu_clear(GIUINTHTSELH, mask);
			irq_set_chip_and_handler(GIU_IRQ(pin),
						 &giuint_high_irq_chip,
						 handle_level_irq);
		}
		giu_write(GIUINTSTATH, mask);
	}
}