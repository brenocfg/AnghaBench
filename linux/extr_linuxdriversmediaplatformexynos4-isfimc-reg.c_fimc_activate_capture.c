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
struct TYPE_2__ {int /*<<< orphan*/  enabled; } ;
struct fimc_ctx {TYPE_1__ scaler; int /*<<< orphan*/  fimc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  fimc_hw_enable_capture (struct fimc_ctx*) ; 
 int /*<<< orphan*/  fimc_hw_enable_scaler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void fimc_activate_capture(struct fimc_ctx *ctx)
{
	fimc_hw_enable_scaler(ctx->fimc_dev, ctx->scaler.enabled);
	fimc_hw_enable_capture(ctx);
}