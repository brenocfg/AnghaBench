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
struct dw_dsi {int /*<<< orphan*/  cur_mode; } ;
struct drm_encoder {int dummy; } ;
struct drm_display_mode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mode_copy (int /*<<< orphan*/ *,struct drm_display_mode*) ; 
 struct dw_dsi* encoder_to_dsi (struct drm_encoder*) ; 

__attribute__((used)) static void dsi_encoder_mode_set(struct drm_encoder *encoder,
				 struct drm_display_mode *mode,
				 struct drm_display_mode *adj_mode)
{
	struct dw_dsi *dsi = encoder_to_dsi(encoder);

	drm_mode_copy(&dsi->cur_mode, adj_mode);
}