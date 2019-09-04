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
struct TYPE_2__ {int* range; scalar_t__* offset; } ;
struct cxl_context {TYPE_1__ irqs; } ;
typedef  scalar_t__ irq_hw_number_t ;
typedef  int __u16 ;

/* Variables and functions */
 int CXL_IRQ_RANGES ; 

__attribute__((used)) static irq_hw_number_t cxl_find_afu_irq(struct cxl_context *ctx, int num)
{
	__u16 range;
	int r;

	for (r = 0; r < CXL_IRQ_RANGES; r++) {
		range = ctx->irqs.range[r];
		if (num < range) {
			return ctx->irqs.offset[r] + num;
		}
		num -= range;
	}
	return 0;
}