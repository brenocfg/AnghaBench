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
 unsigned int HD64461_IRQBASE ; 
 int /*<<< orphan*/  HD64461_NIMR ; 
 unsigned short __raw_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writew (unsigned short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hd64461_mask_irq(struct irq_data *data)
{
	unsigned int irq = data->irq;
	unsigned short nimr;
	unsigned short mask = 1 << (irq - HD64461_IRQBASE);

	nimr = __raw_readw(HD64461_NIMR);
	nimr |= mask;
	__raw_writew(nimr, HD64461_NIMR);
}