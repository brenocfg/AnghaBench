#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ocxl_context {int status; int /*<<< orphan*/  pasid; TYPE_4__* afu; int /*<<< orphan*/  status_mutex; } ;
typedef  enum ocxl_context_status { ____Placeholder_ocxl_context_status } ocxl_context_status ;
struct TYPE_6__ {int dvsec_afu_control_pos; } ;
struct TYPE_8__ {TYPE_3__* fn; int /*<<< orphan*/  afu_control_lock; TYPE_2__ config; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct TYPE_7__ {int /*<<< orphan*/  link; TYPE_1__ dev; } ;

/* Variables and functions */
 int ATTACHED ; 
 int CLOSED ; 
 int EBUSY ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ocxl_config_terminate_pasid (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 int ocxl_link_remove_pe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ocxl_terminate_pasid (int /*<<< orphan*/ ,int) ; 

int ocxl_context_detach(struct ocxl_context *ctx)
{
	struct pci_dev *dev;
	int afu_control_pos;
	enum ocxl_context_status status;
	int rc;

	mutex_lock(&ctx->status_mutex);
	status = ctx->status;
	ctx->status = CLOSED;
	mutex_unlock(&ctx->status_mutex);
	if (status != ATTACHED)
		return 0;

	dev = to_pci_dev(ctx->afu->fn->dev.parent);
	afu_control_pos = ctx->afu->config.dvsec_afu_control_pos;

	mutex_lock(&ctx->afu->afu_control_lock);
	rc = ocxl_config_terminate_pasid(dev, afu_control_pos, ctx->pasid);
	mutex_unlock(&ctx->afu->afu_control_lock);
	trace_ocxl_terminate_pasid(ctx->pasid, rc);
	if (rc) {
		/*
		 * If we timeout waiting for the AFU to terminate the
		 * pasid, then it's dangerous to clean up the Process
		 * Element entry in the SPA, as it may be referenced
		 * in the future by the AFU. In which case, we would
		 * checkstop because of an invalid PE access (FIR
		 * register 2, bit 42). So leave the PE
		 * defined. Caller shouldn't free the context so that
		 * PASID remains allocated.
		 *
		 * A link reset will be required to cleanup the AFU
		 * and the SPA.
		 */
		if (rc == -EBUSY)
			return rc;
	}
	rc = ocxl_link_remove_pe(ctx->afu->fn->link, ctx->pasid);
	if (rc) {
		dev_warn(&dev->dev,
			"Couldn't remove PE entry cleanly: %d\n", rc);
	}
	return 0;
}