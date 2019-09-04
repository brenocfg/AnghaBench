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
struct exynos_dpi {scalar_t__ panel; int /*<<< orphan*/  encoder; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_panel_detach (scalar_t__) ; 
 struct exynos_dpi* encoder_to_dpi (struct drm_encoder*) ; 
 int /*<<< orphan*/  exynos_dpi_disable (int /*<<< orphan*/ *) ; 

int exynos_dpi_remove(struct drm_encoder *encoder)
{
	struct exynos_dpi *ctx = encoder_to_dpi(encoder);

	exynos_dpi_disable(&ctx->encoder);

	if (ctx->panel)
		drm_panel_detach(ctx->panel);

	return 0;
}