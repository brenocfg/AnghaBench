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
struct irq_data {int /*<<< orphan*/  parent_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPI_PROP_ENABLED ; 
 int /*<<< orphan*/  its_vpe_send_inv (struct irq_data*) ; 
 int /*<<< orphan*/  lpi_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void its_vpe_mask_irq(struct irq_data *d)
{
	/*
	 * We need to unmask the LPI, which is described by the parent
	 * irq_data. Instead of calling into the parent (which won't
	 * exactly do the right thing, let's simply use the
	 * parent_data pointer. Yes, I'm naughty.
	 */
	lpi_write_config(d->parent_data, LPI_PROP_ENABLED, 0);
	its_vpe_send_inv(d);
}