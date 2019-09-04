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
struct ipu_soc {int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 int irq_create_mapping (int /*<<< orphan*/ ,int) ; 
 int irq_linear_revmap (int /*<<< orphan*/ ,int) ; 

int ipu_map_irq(struct ipu_soc *ipu, int irq)
{
	int virq;

	virq = irq_linear_revmap(ipu->domain, irq);
	if (!virq)
		virq = irq_create_mapping(ipu->domain, irq);

	return virq;
}