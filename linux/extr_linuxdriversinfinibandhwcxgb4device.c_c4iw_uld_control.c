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
struct TYPE_8__ {int /*<<< orphan*/  pdev; } ;
struct uld_ctx {TYPE_4__ lldi; TYPE_3__* dev; } ;
typedef  enum cxgb4_control { ____Placeholder_cxgb4_control } cxgb4_control ;
struct TYPE_5__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  db_drop; int /*<<< orphan*/  db_empty; int /*<<< orphan*/  db_full; } ;
struct TYPE_6__ {TYPE_1__ stats; } ;
struct TYPE_7__ {TYPE_2__ rdev; } ;

/* Variables and functions */
#define  CXGB4_CONTROL_DB_DROP 130 
#define  CXGB4_CONTROL_DB_EMPTY 129 
#define  CXGB4_CONTROL_DB_FULL 128 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  recover_queues (struct uld_ctx*) ; 
 int /*<<< orphan*/  resume_queues (struct uld_ctx*) ; 
 int /*<<< orphan*/  stop_queues (struct uld_ctx*) ; 

__attribute__((used)) static int c4iw_uld_control(void *handle, enum cxgb4_control control, ...)
{
	struct uld_ctx *ctx = handle;

	switch (control) {
	case CXGB4_CONTROL_DB_FULL:
		stop_queues(ctx);
		ctx->dev->rdev.stats.db_full++;
		break;
	case CXGB4_CONTROL_DB_EMPTY:
		resume_queues(ctx);
		mutex_lock(&ctx->dev->rdev.stats.lock);
		ctx->dev->rdev.stats.db_empty++;
		mutex_unlock(&ctx->dev->rdev.stats.lock);
		break;
	case CXGB4_CONTROL_DB_DROP:
		recover_queues(ctx);
		mutex_lock(&ctx->dev->rdev.stats.lock);
		ctx->dev->rdev.stats.db_drop++;
		mutex_unlock(&ctx->dev->rdev.stats.lock);
		break;
	default:
		pr_warn("%s: unknown control cmd %u\n",
			pci_name(ctx->lldi.pdev), control);
		break;
	}
	return 0;
}