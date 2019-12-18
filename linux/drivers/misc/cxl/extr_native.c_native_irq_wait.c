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
struct cxl_context {int pe; TYPE_1__* afu; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CXL_PSL9_DSISR_PENDING ; 
 int /*<<< orphan*/  CXL_PSL_DSISR_An ; 
 int CXL_PSL_DSISR_PENDING ; 
 int /*<<< orphan*/  CXL_PSL_PEHandle_An ; 
 scalar_t__ cxl_is_power8 () ; 
 scalar_t__ cxl_is_power9 () ; 
 int cxl_p2n_read (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void native_irq_wait(struct cxl_context *ctx)
{
	u64 dsisr;
	int timeout = 1000;
	int ph;

	/*
	 * Wait until no further interrupts are presented by the PSL
	 * for this context.
	 */
	while (timeout--) {
		ph = cxl_p2n_read(ctx->afu, CXL_PSL_PEHandle_An) & 0xffff;
		if (ph != ctx->pe)
			return;
		dsisr = cxl_p2n_read(ctx->afu, CXL_PSL_DSISR_An);
		if (cxl_is_power8() &&
		   ((dsisr & CXL_PSL_DSISR_PENDING) == 0))
			return;
		if (cxl_is_power9() &&
		   ((dsisr & CXL_PSL9_DSISR_PENDING) == 0))
			return;
		/*
		 * We are waiting for the workqueue to process our
		 * irq, so need to let that run here.
		 */
		msleep(1);
	}

	dev_warn(&ctx->afu->dev, "WARNING: waiting on DSI for PE %i"
		 " DSISR %016llx!\n", ph, dsisr);
	return;
}