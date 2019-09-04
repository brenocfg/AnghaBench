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
struct ocxl_context {scalar_t__ status; int /*<<< orphan*/  status_mutex; int /*<<< orphan*/  tidr; int /*<<< orphan*/  pasid; TYPE_2__* afu; } ;
struct TYPE_10__ {TYPE_4__* mm; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct TYPE_9__ {TYPE_1__ context; } ;
struct TYPE_8__ {int /*<<< orphan*/  link; } ;
struct TYPE_7__ {TYPE_3__* fn; } ;

/* Variables and functions */
 scalar_t__ ATTACHED ; 
 int EIO ; 
 scalar_t__ OPENED ; 
 TYPE_5__* current ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ocxl_link_add_pe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,struct ocxl_context*) ; 
 int /*<<< orphan*/  xsl_fault_error ; 

int ocxl_context_attach(struct ocxl_context *ctx, u64 amr)
{
	int rc;

	// Locks both status & tidr
	mutex_lock(&ctx->status_mutex);
	if (ctx->status != OPENED) {
		rc = -EIO;
		goto out;
	}

	rc = ocxl_link_add_pe(ctx->afu->fn->link, ctx->pasid,
			current->mm->context.id, ctx->tidr, amr, current->mm,
			xsl_fault_error, ctx);
	if (rc)
		goto out;

	ctx->status = ATTACHED;
out:
	mutex_unlock(&ctx->status_mutex);
	return rc;
}