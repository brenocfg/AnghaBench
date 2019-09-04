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
struct xgene_rng_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  failure_timer; scalar_t__ failure_cnt; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 struct xgene_rng_dev* ctx ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  failure_timer ; 
 struct xgene_rng_dev* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgene_rng_expired_timer(struct timer_list *t)
{
	struct xgene_rng_dev *ctx = from_timer(ctx, t, failure_timer);

	/* Clear failure counter as timer expired */
	disable_irq(ctx->irq);
	ctx->failure_cnt = 0;
	del_timer(&ctx->failure_timer);
	enable_irq(ctx->irq);
}