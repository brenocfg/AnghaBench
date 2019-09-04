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
struct stm32_exti_chip_data {int dummy; } ;
struct irq_chip_generic {int /*<<< orphan*/  mask_cache; struct stm32_exti_chip_data* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_gc_lock (struct irq_chip_generic*) ; 
 int /*<<< orphan*/  irq_gc_unlock (struct irq_chip_generic*) ; 
 int /*<<< orphan*/  stm32_chip_resume (struct stm32_exti_chip_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stm32_irq_resume(struct irq_chip_generic *gc)
{
	struct stm32_exti_chip_data *chip_data = gc->private;

	irq_gc_lock(gc);
	stm32_chip_resume(chip_data, gc->mask_cache);
	irq_gc_unlock(gc);
}