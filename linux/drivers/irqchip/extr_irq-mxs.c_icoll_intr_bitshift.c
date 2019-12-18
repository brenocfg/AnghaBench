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
typedef  int u32 ;
struct irq_data {int hwirq; } ;

/* Variables and functions */

__attribute__((used)) static u32 icoll_intr_bitshift(struct irq_data *d, u32 bit)
{
	/*
	 * mask lower part of hwirq to convert it
	 * in 0, 1, 2 or 3 and then multiply it by 8 (or shift by 3)
	 */
	return bit << ((d->hwirq & 3) << 3);
}