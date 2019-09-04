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
 int /*<<< orphan*/  atari_enable_irq (unsigned int) ; 
 int /*<<< orphan*/  atari_turnon_irq (unsigned int) ; 
 int /*<<< orphan*/  m68k_irq_startup (struct irq_data*) ; 

__attribute__((used)) static unsigned int atari_irq_startup(struct irq_data *data)
{
	unsigned int irq = data->irq;

	m68k_irq_startup(data);
	atari_turnon_irq(irq);
	atari_enable_irq(irq);
	return 0;
}