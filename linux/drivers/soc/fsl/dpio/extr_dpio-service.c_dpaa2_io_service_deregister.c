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
typedef  int /*<<< orphan*/  u16 ;
struct dpaa2_io_notification_ctx {int /*<<< orphan*/  node; scalar_t__ id; scalar_t__ is_cdan; struct dpaa2_io* dpio_private; } ;
struct dpaa2_io {int /*<<< orphan*/  lock_notifications; int /*<<< orphan*/  swp; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qbman_swp_CDAN_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void dpaa2_io_service_deregister(struct dpaa2_io *service,
				 struct dpaa2_io_notification_ctx *ctx,
				 struct device *dev)
{
	struct dpaa2_io *d = ctx->dpio_private;
	unsigned long irqflags;

	if (ctx->is_cdan)
		qbman_swp_CDAN_disable(d->swp, (u16)ctx->id);

	spin_lock_irqsave(&d->lock_notifications, irqflags);
	list_del(&ctx->node);
	spin_unlock_irqrestore(&d->lock_notifications, irqflags);

}