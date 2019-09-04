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
struct uld_ctx {TYPE_5__* dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  db_fc_interruptions; int /*<<< orphan*/  db_state_transitions; } ;
struct TYPE_7__ {int dbfifo_int_thresh; int /*<<< orphan*/ * ports; } ;
struct TYPE_9__ {int flags; TYPE_3__ stats; TYPE_2__ lldi; TYPE_1__* status_page; } ;
struct TYPE_10__ {scalar_t__ db_state; int /*<<< orphan*/  lock; TYPE_4__ rdev; int /*<<< orphan*/  db_fc_list; int /*<<< orphan*/  qpidr; } ;
struct TYPE_6__ {scalar_t__ db_off; } ;

/* Variables and functions */
 int DB_FC_DRAIN_THRESH ; 
 scalar_t__ DB_FC_RESUME_DELAY ; 
 scalar_t__ FLOW_CONTROL ; 
 scalar_t__ NORMAL ; 
 scalar_t__ STOPPED ; 
 int T4_STATUS_PAGE_DISABLED ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int cxgb4_dbfifo_count (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  enable_qp_db ; 
 int /*<<< orphan*/  idr_for_each (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resume_a_chunk (struct uld_ctx*) ; 
 int /*<<< orphan*/  schedule_timeout (scalar_t__) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void resume_queues(struct uld_ctx *ctx)
{
	spin_lock_irq(&ctx->dev->lock);
	if (ctx->dev->db_state != STOPPED)
		goto out;
	ctx->dev->db_state = FLOW_CONTROL;
	while (1) {
		if (list_empty(&ctx->dev->db_fc_list)) {
			WARN_ON(ctx->dev->db_state != FLOW_CONTROL);
			ctx->dev->db_state = NORMAL;
			ctx->dev->rdev.stats.db_state_transitions++;
			if (ctx->dev->rdev.flags & T4_STATUS_PAGE_DISABLED) {
				idr_for_each(&ctx->dev->qpidr, enable_qp_db,
					     NULL);
			} else {
				ctx->dev->rdev.status_page->db_off = 0;
			}
			break;
		} else {
			if (cxgb4_dbfifo_count(ctx->dev->rdev.lldi.ports[0], 1)
			    < (ctx->dev->rdev.lldi.dbfifo_int_thresh <<
			       DB_FC_DRAIN_THRESH)) {
				resume_a_chunk(ctx);
			}
			if (!list_empty(&ctx->dev->db_fc_list)) {
				spin_unlock_irq(&ctx->dev->lock);
				if (DB_FC_RESUME_DELAY) {
					set_current_state(TASK_UNINTERRUPTIBLE);
					schedule_timeout(DB_FC_RESUME_DELAY);
				}
				spin_lock_irq(&ctx->dev->lock);
				if (ctx->dev->db_state != FLOW_CONTROL)
					break;
			}
		}
	}
out:
	if (ctx->dev->db_state != NORMAL)
		ctx->dev->rdev.stats.db_fc_interruptions++;
	spin_unlock_irq(&ctx->dev->lock);
}