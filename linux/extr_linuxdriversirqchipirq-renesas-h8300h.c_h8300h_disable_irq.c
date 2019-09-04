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
struct irq_data {int irq; } ;

/* Variables and functions */
 scalar_t__ IPR ; 
 int /*<<< orphan*/  ctrl_bclr (int,scalar_t__) ; 
 int* ipr_bit ; 

__attribute__((used)) static void h8300h_disable_irq(struct irq_data *data)
{
	int bit;
	int irq = data->irq - 12;

	bit = ipr_bit[irq];
	if (bit >= 0) {
		if (bit < 8)
			ctrl_bclr(bit & 7, IPR);
		else
			ctrl_bclr(bit & 7, (IPR+1));
	}
}