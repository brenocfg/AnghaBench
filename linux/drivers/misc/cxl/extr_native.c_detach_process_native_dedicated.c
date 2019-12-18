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
struct cxl_context {int /*<<< orphan*/  afu; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* afu_reset ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cxl_afu_disable (int /*<<< orphan*/ ) ; 
 TYPE_1__* cxl_ops ; 
 int /*<<< orphan*/  cxl_psl_purge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int detach_process_native_dedicated(struct cxl_context *ctx)
{
	/*
	 * The CAIA section 2.1.1 indicates that we need to do an AFU reset to
	 * stop the AFU in dedicated mode (we therefore do not make that
	 * optional like we do in the afu directed path). It does not indicate
	 * that we need to do an explicit disable (which should occur
	 * implicitly as part of the reset) or purge, but we do these as well
	 * to be on the safe side.
	 *
	 * Notably we used to have some issues with the disable sequence
	 * (before the sequence was spelled out in the architecture) which is
	 * why we were so heavy weight in the first place, however a bug was
	 * discovered that had rendered the disable operation ineffective, so
	 * it is conceivable that was the sole explanation for those
	 * difficulties. Point is, we should be careful and do some regression
	 * testing if we ever attempt to remove any part of this procedure.
	 */
	cxl_ops->afu_reset(ctx->afu);
	cxl_afu_disable(ctx->afu);
	cxl_psl_purge(ctx->afu);
	return 0;
}