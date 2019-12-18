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
struct cxl_context {struct cxl_afu_driver_ops* afu_driver_ops; int /*<<< orphan*/  afu_driver_events; } ;
struct cxl_afu_driver_ops {int /*<<< orphan*/  event_delivered; int /*<<< orphan*/  fetch_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void cxl_set_driver_ops(struct cxl_context *ctx,
			struct cxl_afu_driver_ops *ops)
{
	WARN_ON(!ops->fetch_event || !ops->event_delivered);
	atomic_set(&ctx->afu_driver_events, 0);
	ctx->afu_driver_ops = ops;
}