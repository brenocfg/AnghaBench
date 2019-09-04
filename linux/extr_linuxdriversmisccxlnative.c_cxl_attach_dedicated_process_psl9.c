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
typedef  int /*<<< orphan*/  u64 ;
struct cxl_context {TYPE_1__* elem; struct cxl_afu* afu; } ;
struct cxl_afu {TYPE_4__* adapter; } ;
struct TYPE_10__ {int (* afu_reset ) (struct cxl_afu*) ;} ;
struct TYPE_9__ {TYPE_3__* native; } ;
struct TYPE_8__ {TYPE_2__* sl_ops; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* update_dedicated_ivtes ) (struct cxl_context*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  software_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_PE_SOFTWARE_STATE_V ; 
 int afu_enable (struct cxl_afu*) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 TYPE_5__* cxl_ops ; 
 int process_element_entry_psl9 (struct cxl_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct cxl_context*) ; 
 int stub2 (struct cxl_afu*) ; 

int cxl_attach_dedicated_process_psl9(struct cxl_context *ctx, u64 wed, u64 amr)
{
	struct cxl_afu *afu = ctx->afu;
	int result;

	/* fill the process element entry */
	result = process_element_entry_psl9(ctx, wed, amr);
	if (result)
		return result;

	if (ctx->afu->adapter->native->sl_ops->update_dedicated_ivtes)
		afu->adapter->native->sl_ops->update_dedicated_ivtes(ctx);

	ctx->elem->software_state = cpu_to_be32(CXL_PE_SOFTWARE_STATE_V);
	/*
	 * Ideally we should do a wmb() here to make sure the changes to the
	 * PE are visible to the card before we call afu_enable.
	 * On ppc64 though all mmios are preceded by a 'sync' instruction hence
	 * we dont dont need one here.
	 */

	result = cxl_ops->afu_reset(afu);
	if (result)
		return result;

	return afu_enable(afu);
}