#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct dpaa2_io_notification_ctx {scalar_t__ qman64; scalar_t__ id; scalar_t__ is_cdan; int /*<<< orphan*/  node; struct dpaa2_io* dpio_private; int /*<<< orphan*/  dpio_id; int /*<<< orphan*/  desired_cpu; } ;
struct TYPE_2__ {int /*<<< orphan*/  dpio_id; } ;
struct dpaa2_io {int /*<<< orphan*/  swp; int /*<<< orphan*/  lock_notifications; int /*<<< orphan*/  notifications; TYPE_1__ dpio_desc; int /*<<< orphan*/  dev; } ;
struct device_link {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DL_FLAG_AUTOREMOVE_CONSUMER ; 
 int EINVAL ; 
 int ENODEV ; 
 struct device_link* device_link_add (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int qbman_swp_CDAN_set_context_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct dpaa2_io* service_select_by_cpu (struct dpaa2_io*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int dpaa2_io_service_register(struct dpaa2_io *d,
			      struct dpaa2_io_notification_ctx *ctx,
			      struct device *dev)
{
	struct device_link *link;
	unsigned long irqflags;

	d = service_select_by_cpu(d, ctx->desired_cpu);
	if (!d)
		return -ENODEV;

	link = device_link_add(dev, d->dev, DL_FLAG_AUTOREMOVE_CONSUMER);
	if (!link)
		return -EINVAL;

	ctx->dpio_id = d->dpio_desc.dpio_id;
	ctx->qman64 = (u64)(uintptr_t)ctx;
	ctx->dpio_private = d;
	spin_lock_irqsave(&d->lock_notifications, irqflags);
	list_add(&ctx->node, &d->notifications);
	spin_unlock_irqrestore(&d->lock_notifications, irqflags);

	/* Enable the generation of CDAN notifications */
	if (ctx->is_cdan)
		return qbman_swp_CDAN_set_context_enable(d->swp,
							 (u16)ctx->id,
							 ctx->qman64);
	return 0;
}