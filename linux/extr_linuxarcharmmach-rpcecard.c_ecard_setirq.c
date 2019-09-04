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
struct expansion_card_ops {int dummy; } ;
struct expansion_card {struct expansion_card_ops const* ops; void* irq_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  barrier () ; 

void ecard_setirq(struct expansion_card *ec, const struct expansion_card_ops *ops, void *irq_data)
{
	ec->irq_data = irq_data;
	barrier();
	ec->ops = ops;
}