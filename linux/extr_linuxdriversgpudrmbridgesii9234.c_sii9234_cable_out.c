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
 int /*<<< orphan*/  TPI_DPD_REG ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sii9234_hw_off (struct sii9234*) ; 
 TYPE_1__* to_i2c_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpi_writeb (struct sii9234*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sii9234_cable_out(struct sii9234 *ctx)
{
	mutex_lock(&ctx->lock);

	if (ctx->state == ST_OFF)
		goto unlock;

	disable_irq(to_i2c_client(ctx->dev)->irq);
	tpi_writeb(ctx, TPI_DPD_REG, 0);
	/* Turn on&off hpd festure for only QCT HDMI */
	sii9234_hw_off(ctx);

	ctx->state = ST_OFF;

unlock:
	mutex_unlock(&ctx->lock);
}