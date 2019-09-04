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
struct exynos_drm_crtc {struct decon_context* ctx; } ;
struct decon_context {scalar_t__ suspended; } ;

/* Variables and functions */
 int WINDOWS_NR ; 
 int /*<<< orphan*/  decon_shadow_protect_win (struct decon_context*,int,int) ; 

__attribute__((used)) static void decon_atomic_begin(struct exynos_drm_crtc *crtc)
{
	struct decon_context *ctx = crtc->ctx;
	int i;

	if (ctx->suspended)
		return;

	for (i = 0; i < WINDOWS_NR; i++)
		decon_shadow_protect_win(ctx, i, true);
}