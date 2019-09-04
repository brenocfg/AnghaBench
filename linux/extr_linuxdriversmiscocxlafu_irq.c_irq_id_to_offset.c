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
typedef  scalar_t__ u64 ;
struct ocxl_context {TYPE_1__* afu; } ;
struct TYPE_2__ {scalar_t__ irq_base_offset; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 

__attribute__((used)) static u64 irq_id_to_offset(struct ocxl_context *ctx, int id)
{
	return ctx->afu->irq_base_offset + (id << PAGE_SHIFT);
}