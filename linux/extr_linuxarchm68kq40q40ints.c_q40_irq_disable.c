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
struct irq_data {unsigned int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT_ENABLE_REG ; 
 int /*<<< orphan*/  master_outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mext_disabled ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 

void q40_irq_disable(struct irq_data *data)
{
	unsigned int irq = data->irq;

	/* disable ISA iqs : only do something if the driver has been
	 * verified to be Q40 "compatible" - right now IDE, NE2K
	 * Any driver should not attempt to sleep across disable_irq !!
	 */

	if (irq >= 5 && irq <= 15) {
		master_outb(0, EXT_ENABLE_REG);
		mext_disabled++;
		if (mext_disabled > 1)
			pr_info("disable_irq nesting count %d\n",
				mext_disabled);
	}
}