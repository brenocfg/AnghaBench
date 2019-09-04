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
typedef  scalar_t__ u32 ;
struct fimd_context {TYPE_1__* crtc; int /*<<< orphan*/  irq_flags; int /*<<< orphan*/  wait_vsync_queue; int /*<<< orphan*/  wait_vsync_event; int /*<<< orphan*/  dev; int /*<<< orphan*/  win_updated; int /*<<< orphan*/  drm_dev; TYPE_2__* driver_data; } ;
struct exynos_drm_crtc {struct fimd_context* ctx; } ;
struct TYPE_4__ {scalar_t__ trg_type; } ;
struct TYPE_3__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 scalar_t__ I80_HW_TRG ; 
 scalar_t__ atomic_add_unless (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_crtc_handle_vblank (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fimd_trigger (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fimd_te_handler(struct exynos_drm_crtc *crtc)
{
	struct fimd_context *ctx = crtc->ctx;
	u32 trg_type = ctx->driver_data->trg_type;

	/* Checks the crtc is detached already from encoder */
	if (!ctx->drm_dev)
		return;

	if (trg_type == I80_HW_TRG)
		goto out;

	/*
	 * If there is a page flip request, triggers and handles the page flip
	 * event so that current fb can be updated into panel GRAM.
	 */
	if (atomic_add_unless(&ctx->win_updated, -1, 0))
		fimd_trigger(ctx->dev);

out:
	/* Wakes up vsync event queue */
	if (atomic_read(&ctx->wait_vsync_event)) {
		atomic_set(&ctx->wait_vsync_event, 0);
		wake_up(&ctx->wait_vsync_queue);
	}

	if (test_bit(0, &ctx->irq_flags))
		drm_crtc_handle_vblank(&ctx->crtc->base);
}