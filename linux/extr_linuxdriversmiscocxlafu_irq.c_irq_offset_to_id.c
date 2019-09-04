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
typedef  int u64 ;
struct ocxl_context {TYPE_1__* afu; } ;
struct TYPE_2__ {int irq_base_offset; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 

__attribute__((used)) static int irq_offset_to_id(struct ocxl_context *ctx, u64 offset)
{
	return (offset - ctx->afu->irq_base_offset) >> PAGE_SHIFT;
}