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
typedef  void* u64 ;
struct cxl_context {int /*<<< orphan*/  fault_work; void* dar; void* dsisr; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t schedule_cxl_fault(struct cxl_context *ctx, u64 dsisr, u64 dar)
{
	ctx->dsisr = dsisr;
	ctx->dar = dar;
	schedule_work(&ctx->fault_work);
	return IRQ_HANDLED;
}