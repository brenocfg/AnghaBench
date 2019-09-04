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
struct drm_encoder {int /*<<< orphan*/  crtc; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct drm_display_mode {int /*<<< orphan*/  flags; int /*<<< orphan*/  type; int /*<<< orphan*/  vtotal; int /*<<< orphan*/  vsync_end; int /*<<< orphan*/  vsync_start; int /*<<< orphan*/  vdisplay; int /*<<< orphan*/  htotal; int /*<<< orphan*/  hsync_end; int /*<<< orphan*/  hsync_start; int /*<<< orphan*/  hdisplay; int /*<<< orphan*/  clock; int /*<<< orphan*/  vrefresh; int /*<<< orphan*/  name; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdp5_crtc_set_pipeline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pingpong_tearcheck_setup (struct drm_encoder*,struct drm_display_mode*) ; 

void mdp5_cmd_encoder_mode_set(struct drm_encoder *encoder,
			       struct drm_display_mode *mode,
			       struct drm_display_mode *adjusted_mode)
{
	mode = adjusted_mode;

	DBG("set mode: %d:\"%s\" %d %d %d %d %d %d %d %d %d %d 0x%x 0x%x",
			mode->base.id, mode->name,
			mode->vrefresh, mode->clock,
			mode->hdisplay, mode->hsync_start,
			mode->hsync_end, mode->htotal,
			mode->vdisplay, mode->vsync_start,
			mode->vsync_end, mode->vtotal,
			mode->type, mode->flags);
	pingpong_tearcheck_setup(encoder, mode);
	mdp5_crtc_set_pipeline(encoder->crtc);
}