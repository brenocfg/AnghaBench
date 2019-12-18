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
typedef  int /*<<< orphan*/  u64 ;
struct mm_struct {int dummy; } ;
struct cxl_context {int /*<<< orphan*/  pe; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ack_irq ) (struct cxl_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_PSL_TFC_An_R ; 
 int /*<<< orphan*/  cxl_ack_ae (struct cxl_context*) ; 
 scalar_t__ cxl_handle_mm_fault (struct mm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* cxl_ops ; 
 int /*<<< orphan*/  pr_devel (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct cxl_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_cxl_pte_miss (struct cxl_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cxl_handle_page_fault(struct cxl_context *ctx,
				  struct mm_struct *mm,
				  u64 dsisr, u64 dar)
{
	trace_cxl_pte_miss(ctx, dsisr, dar);

	if (cxl_handle_mm_fault(mm, dsisr, dar)) {
		cxl_ack_ae(ctx);
	} else {
		pr_devel("Page fault successfully handled for pe: %i!\n", ctx->pe);
		cxl_ops->ack_irq(ctx, CXL_PSL_TFC_An_R, 0);
	}
}