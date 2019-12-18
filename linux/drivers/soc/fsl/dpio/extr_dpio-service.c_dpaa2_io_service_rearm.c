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
struct dpaa2_io_notification_ctx {scalar_t__ id; scalar_t__ is_cdan; int /*<<< orphan*/  desired_cpu; } ;
struct dpaa2_io {int /*<<< orphan*/  lock_mgmt_cmd; int /*<<< orphan*/  swp; } ;

/* Variables and functions */
 int ENODEV ; 
 int qbman_swp_CDAN_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qbman_swp_fq_schedule (int /*<<< orphan*/ ,scalar_t__) ; 
 struct dpaa2_io* service_select_by_cpu (struct dpaa2_io*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  unlikely (struct dpaa2_io*) ; 

int dpaa2_io_service_rearm(struct dpaa2_io *d,
			   struct dpaa2_io_notification_ctx *ctx)
{
	unsigned long irqflags;
	int err;

	d = service_select_by_cpu(d, ctx->desired_cpu);
	if (!unlikely(d))
		return -ENODEV;

	spin_lock_irqsave(&d->lock_mgmt_cmd, irqflags);
	if (ctx->is_cdan)
		err = qbman_swp_CDAN_enable(d->swp, (u16)ctx->id);
	else
		err = qbman_swp_fq_schedule(d->swp, ctx->id);
	spin_unlock_irqrestore(&d->lock_mgmt_cmd, irqflags);

	return err;
}