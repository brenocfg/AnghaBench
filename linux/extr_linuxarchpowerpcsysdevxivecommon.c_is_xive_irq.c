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
struct irq_chip {int dummy; } ;

/* Variables and functions */
 struct irq_chip xive_irq_chip ; 

bool is_xive_irq(struct irq_chip *chip)
{
	return chip == &xive_irq_chip;
}