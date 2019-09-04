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
struct cxl_context {TYPE_3__* afu; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_10__ {int /*<<< orphan*/  (* ack_irq ) (struct cxl_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {TYPE_2__* native; } ;
struct TYPE_8__ {TYPE_4__* adapter; int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {TYPE_1__* sl_ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* debugfs_stop_trace ) (TYPE_4__*) ;int /*<<< orphan*/  (* psl_irq_dump_registers ) (struct cxl_context*) ;} ;

/* Variables and functions */
 TYPE_5__* cxl_ops ; 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  stub1 (struct cxl_context*) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub3 (struct cxl_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t native_handle_psl_slice_error(struct cxl_context *ctx,
						u64 dsisr, u64 errstat)
{

	dev_crit(&ctx->afu->dev, "PSL ERROR STATUS: 0x%016llx\n", errstat);

	if (ctx->afu->adapter->native->sl_ops->psl_irq_dump_registers)
		ctx->afu->adapter->native->sl_ops->psl_irq_dump_registers(ctx);

	if (ctx->afu->adapter->native->sl_ops->debugfs_stop_trace) {
		dev_crit(&ctx->afu->dev, "STOPPING CXL TRACE\n");
		ctx->afu->adapter->native->sl_ops->debugfs_stop_trace(ctx->afu->adapter);
	}

	return cxl_ops->ack_irq(ctx, 0, errstat);
}