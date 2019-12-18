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
struct sii9234 {scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 scalar_t__ ST_OFF ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sii9234_goto_d3 (struct sii9234*) ; 
 int sii9234_hw_on (struct sii9234*) ; 
 int /*<<< orphan*/  sii9234_hw_reset (struct sii9234*) ; 
 TYPE_1__* to_i2c_client (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sii9234_cable_in(struct sii9234 *ctx)
{
	int ret;

	mutex_lock(&ctx->lock);
	if (ctx->state != ST_OFF)
		goto unlock;
	ret = sii9234_hw_on(ctx);
	if (ret < 0)
		goto unlock;

	sii9234_hw_reset(ctx);
	sii9234_goto_d3(ctx);
	/* To avoid irq storm, when hw is in meta state */
	enable_irq(to_i2c_client(ctx->dev)->irq);

unlock:
	mutex_unlock(&ctx->lock);
}