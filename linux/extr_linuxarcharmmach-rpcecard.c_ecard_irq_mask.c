#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct irq_data {int /*<<< orphan*/  irq; } ;
struct TYPE_5__ {TYPE_4__* ops; } ;
typedef  TYPE_1__ ecard_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* irqdisable ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_4__ ecard_default_ops ; 
 TYPE_1__* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ecard_irq_mask(struct irq_data *d)
{
	ecard_t *ec = irq_data_get_irq_chip_data(d);

	if (ec) {
		if (!ec->ops)
			ec->ops = &ecard_default_ops;

		if (ec->ops && ec->ops->irqdisable)
			ec->ops->irqdisable(ec, d->irq);
	}
}