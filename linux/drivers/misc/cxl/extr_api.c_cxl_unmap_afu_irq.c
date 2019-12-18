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
struct cxl_context {int dummy; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  cxl_find_afu_irq (struct cxl_context*,int) ; 
 int /*<<< orphan*/  cxl_unmap_irq (unsigned int,void*) ; 
 unsigned int irq_find_mapping (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void cxl_unmap_afu_irq(struct cxl_context *ctx, int num, void *cookie)
{
	irq_hw_number_t hwirq;
	unsigned int virq;

	hwirq = cxl_find_afu_irq(ctx, num);
	if (!hwirq)
		return;

	virq = irq_find_mapping(NULL, hwirq);
	if (virq)
		cxl_unmap_irq(virq, cookie);
}