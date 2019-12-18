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
struct mtk_dsi {int /*<<< orphan*/  vm; } ;
struct drm_encoder {int dummy; } ;
struct drm_display_mode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_display_mode_to_videomode (struct drm_display_mode*,int /*<<< orphan*/ *) ; 
 struct mtk_dsi* encoder_to_dsi (struct drm_encoder*) ; 

__attribute__((used)) static void mtk_dsi_encoder_mode_set(struct drm_encoder *encoder,
				     struct drm_display_mode *mode,
				     struct drm_display_mode *adjusted)
{
	struct mtk_dsi *dsi = encoder_to_dsi(encoder);

	drm_display_mode_to_videomode(adjusted, &dsi->vm);
}