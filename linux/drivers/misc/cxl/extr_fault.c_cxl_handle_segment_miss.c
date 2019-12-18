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
 int IRQ_HANDLED ; 
 int /*<<< orphan*/  cxl_ack_ae (struct cxl_context*) ; 
 int cxl_fault_segment (struct cxl_context*,struct mm_struct*,int /*<<< orphan*/ ) ; 
 TYPE_1__* cxl_ops ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  pr_devel (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct cxl_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_cxl_ste_miss (struct cxl_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cxl_handle_segment_miss(struct cxl_context *ctx,
				   struct mm_struct *mm, u64 ea)
{
	int rc;

	pr_devel("CXL interrupt: Segment fault pe: %i ea: %#llx\n", ctx->pe, ea);
	trace_cxl_ste_miss(ctx, ea);

	if ((rc = cxl_fault_segment(ctx, mm, ea)))
		cxl_ack_ae(ctx);
	else {

		mb(); /* Order seg table write to TFC MMIO write */
		cxl_ops->ack_irq(ctx, CXL_PSL_TFC_An_R, 0);
	}

	return IRQ_HANDLED;
}