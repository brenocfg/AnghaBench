#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ionic_queue {TYPE_1__* head; } ;
struct ionic_lif {int /*<<< orphan*/  adminq_lock; TYPE_2__* netdev; TYPE_3__* adminqcq; } ;
struct ionic_admin_ctx {int /*<<< orphan*/  cmd; } ;
struct TYPE_6__ {struct ionic_queue q; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int ENOSPC ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dynamic_hex_dump (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  ionic_adminq_cb ; 
 int /*<<< orphan*/  ionic_q_has_space (struct ionic_queue*,int) ; 
 int /*<<< orphan*/  ionic_q_post (struct ionic_queue*,int,int /*<<< orphan*/ ,struct ionic_admin_ctx*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ionic_adminq_post(struct ionic_lif *lif, struct ionic_admin_ctx *ctx)
{
	struct ionic_queue *adminq = &lif->adminqcq->q;
	int err = 0;

	WARN_ON(in_interrupt());

	spin_lock(&lif->adminq_lock);
	if (!ionic_q_has_space(adminq, 1)) {
		err = -ENOSPC;
		goto err_out;
	}

	memcpy(adminq->head->desc, &ctx->cmd, sizeof(ctx->cmd));

	dev_dbg(&lif->netdev->dev, "post admin queue command:\n");
	dynamic_hex_dump("cmd ", DUMP_PREFIX_OFFSET, 16, 1,
			 &ctx->cmd, sizeof(ctx->cmd), true);

	ionic_q_post(adminq, true, ionic_adminq_cb, ctx);

err_out:
	spin_unlock(&lif->adminq_lock);

	return err;
}