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
struct uld_ctx {TYPE_4__* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  db_state_transitions; } ;
struct TYPE_7__ {int flags; TYPE_2__* status_page; TYPE_1__ stats; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; TYPE_3__ rdev; int /*<<< orphan*/  qpidr; int /*<<< orphan*/  db_state; } ;
struct TYPE_6__ {int db_off; } ;

/* Variables and functions */
 int /*<<< orphan*/  STOPPED ; 
 int T4_STATUS_PAGE_DISABLED ; 
 int /*<<< orphan*/  disable_qp_db ; 
 int /*<<< orphan*/  idr_for_each (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void stop_queues(struct uld_ctx *ctx)
{
	unsigned long flags;

	spin_lock_irqsave(&ctx->dev->lock, flags);
	ctx->dev->rdev.stats.db_state_transitions++;
	ctx->dev->db_state = STOPPED;
	if (ctx->dev->rdev.flags & T4_STATUS_PAGE_DISABLED)
		idr_for_each(&ctx->dev->qpidr, disable_qp_db, NULL);
	else
		ctx->dev->rdev.status_page->db_off = 1;
	spin_unlock_irqrestore(&ctx->dev->lock, flags);
}