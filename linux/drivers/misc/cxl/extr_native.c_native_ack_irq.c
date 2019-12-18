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
typedef  scalar_t__ u64 ;
struct cxl_context {int /*<<< orphan*/  afu; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_PSL_TFC_An ; 
 int /*<<< orphan*/  cxl_p2n_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  recover_psl_err (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  trace_cxl_psl_irq_ack (struct cxl_context*,scalar_t__) ; 

__attribute__((used)) static int native_ack_irq(struct cxl_context *ctx, u64 tfc, u64 psl_reset_mask)
{
	trace_cxl_psl_irq_ack(ctx, tfc);
	if (tfc)
		cxl_p2n_write(ctx->afu, CXL_PSL_TFC_An, tfc);
	if (psl_reset_mask)
		recover_psl_err(ctx->afu, psl_reset_mask);

	return 0;
}