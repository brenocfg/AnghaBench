#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct cxl_context {struct cxl_afu* afu; int /*<<< orphan*/  sstp1; int /*<<< orphan*/  sstp0; scalar_t__ kernel; } ;
struct cxl_afu {TYPE_3__* adapter; } ;
struct TYPE_10__ {scalar_t__ pid; } ;
struct TYPE_9__ {int (* afu_reset ) (struct cxl_afu*) ;} ;
struct TYPE_8__ {TYPE_2__* native; } ;
struct TYPE_7__ {TYPE_1__* sl_ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* update_dedicated_ivtes ) (struct cxl_context*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_PSL_AMR_An ; 
 int /*<<< orphan*/  CXL_PSL_PID_TID_An ; 
 int /*<<< orphan*/  CXL_PSL_SR_An ; 
 int /*<<< orphan*/  CXL_PSL_WED_An ; 
 int afu_enable (struct cxl_afu*) ; 
 int /*<<< orphan*/  calculate_sr (struct cxl_context*) ; 
 TYPE_5__* current ; 
 int /*<<< orphan*/  cxl_assign_psn_space (struct cxl_context*) ; 
 TYPE_4__* cxl_ops ; 
 int /*<<< orphan*/  cxl_p1n_write (struct cxl_afu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxl_p2n_write (struct cxl_afu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cxl_prefault (struct cxl_context*,int) ; 
 int cxl_write_sstp (struct cxl_afu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct cxl_context*) ; 
 int stub2 (struct cxl_afu*) ; 

int cxl_attach_dedicated_process_psl8(struct cxl_context *ctx, u64 wed, u64 amr)
{
	struct cxl_afu *afu = ctx->afu;
	u64 pid;
	int rc;

	pid = (u64)current->pid << 32;
	if (ctx->kernel)
		pid = 0;
	cxl_p2n_write(afu, CXL_PSL_PID_TID_An, pid);

	cxl_p1n_write(afu, CXL_PSL_SR_An, calculate_sr(ctx));

	if ((rc = cxl_write_sstp(afu, ctx->sstp0, ctx->sstp1)))
		return rc;

	cxl_prefault(ctx, wed);

	if (ctx->afu->adapter->native->sl_ops->update_dedicated_ivtes)
		afu->adapter->native->sl_ops->update_dedicated_ivtes(ctx);

	cxl_p2n_write(afu, CXL_PSL_AMR_An, amr);

	/* master only context for dedicated */
	cxl_assign_psn_space(ctx);

	if ((rc = cxl_ops->afu_reset(afu)))
		return rc;

	cxl_p2n_write(afu, CXL_PSL_WED_An, wed);

	return afu_enable(afu);
}