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

__attribute__((used)) static void its_vpe_unmask_irq(struct irq_data *d)
{
	/* Same hack as above... */
	lpi_write_config(d->parent_data, 0, LPI_PROP_ENABLED);
	its_vpe_send_inv(d);
}