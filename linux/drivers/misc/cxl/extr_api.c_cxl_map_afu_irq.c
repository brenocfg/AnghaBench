#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cxl_context {TYPE_1__* afu; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;
typedef  int /*<<< orphan*/  irq_handler_t ;
struct TYPE_2__ {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  cxl_find_afu_irq (struct cxl_context*,int) ; 
 int cxl_map_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,char*) ; 

int cxl_map_afu_irq(struct cxl_context *ctx, int num,
		    irq_handler_t handler, void *cookie, char *name)
{
	irq_hw_number_t hwirq;

	/*
	 * Find interrupt we are to register.
	 */
	hwirq = cxl_find_afu_irq(ctx, num);
	if (!hwirq)
		return -ENOENT;

	return cxl_map_irq(ctx->afu->adapter, hwirq, handler, cookie, name);
}