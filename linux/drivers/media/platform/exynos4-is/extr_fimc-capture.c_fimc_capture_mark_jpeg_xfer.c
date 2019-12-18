#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int enabled; } ;
struct fimc_ctx {TYPE_2__* fimc_dev; TYPE_1__ scaler; } ;
typedef  enum fimc_color_fmt { ____Placeholder_fimc_color_fmt } fimc_color_fmt ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST_CAPT_JPEG ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fimc_ctrls_activate (struct fimc_ctx*,int) ; 
 int fimc_fmt_is_user_defined (int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fimc_capture_mark_jpeg_xfer(struct fimc_ctx *ctx,
					enum fimc_color_fmt color)
{
	bool jpeg = fimc_fmt_is_user_defined(color);

	ctx->scaler.enabled = !jpeg;
	fimc_ctrls_activate(ctx, !jpeg);

	if (jpeg)
		set_bit(ST_CAPT_JPEG, &ctx->fimc_dev->state);
	else
		clear_bit(ST_CAPT_JPEG, &ctx->fimc_dev->state);
}