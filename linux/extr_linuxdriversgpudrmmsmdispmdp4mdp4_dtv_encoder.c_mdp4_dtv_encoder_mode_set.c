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
typedef  int uint32_t ;
struct mdp4_kms {int dummy; } ;
struct mdp4_dtv_encoder {int pixclock; } ;
struct drm_encoder {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct drm_display_mode {int clock; int hdisplay; int hsync_start; int hsync_end; int htotal; int vdisplay; int vsync_start; int vsync_end; int vtotal; int flags; int /*<<< orphan*/  type; int /*<<< orphan*/  vrefresh; int /*<<< orphan*/  name; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int,...) ; 
 int DRM_MODE_FLAG_NHSYNC ; 
 int DRM_MODE_FLAG_NVSYNC ; 
 int MDP4_DTV_ACTIVE_HCTL_END (int /*<<< orphan*/ ) ; 
 int MDP4_DTV_ACTIVE_HCTL_START (int /*<<< orphan*/ ) ; 
 int MDP4_DTV_CTRL_POLARITY_HSYNC_LOW ; 
 int MDP4_DTV_CTRL_POLARITY_VSYNC_LOW ; 
 int MDP4_DTV_DISPLAY_HCTRL_END (int) ; 
 int MDP4_DTV_DISPLAY_HCTRL_START (int) ; 
 int MDP4_DTV_HSYNC_CTRL_PERIOD (int) ; 
 int MDP4_DTV_HSYNC_CTRL_PULSEW (int) ; 
 int MDP4_DTV_UNDERFLOW_CLR_COLOR (int) ; 
 int MDP4_DTV_UNDERFLOW_CLR_ENABLE_RECOVERY ; 
 int /*<<< orphan*/  REG_MDP4_DTV_ACTIVE_HCTL ; 
 int /*<<< orphan*/  REG_MDP4_DTV_ACTIVE_VEND ; 
 int /*<<< orphan*/  REG_MDP4_DTV_ACTIVE_VSTART ; 
 int /*<<< orphan*/  REG_MDP4_DTV_BORDER_CLR ; 
 int /*<<< orphan*/  REG_MDP4_DTV_CTRL_POLARITY ; 
 int /*<<< orphan*/  REG_MDP4_DTV_DISPLAY_HCTRL ; 
 int /*<<< orphan*/  REG_MDP4_DTV_DISPLAY_VEND ; 
 int /*<<< orphan*/  REG_MDP4_DTV_DISPLAY_VSTART ; 
 int /*<<< orphan*/  REG_MDP4_DTV_HSYNC_CTRL ; 
 int /*<<< orphan*/  REG_MDP4_DTV_HSYNC_SKEW ; 
 int /*<<< orphan*/  REG_MDP4_DTV_UNDERFLOW_CLR ; 
 int /*<<< orphan*/  REG_MDP4_DTV_VSYNC_LEN ; 
 int /*<<< orphan*/  REG_MDP4_DTV_VSYNC_PERIOD ; 
 struct mdp4_kms* get_kms (struct drm_encoder*) ; 
 int /*<<< orphan*/  mdp4_write (struct mdp4_kms*,int /*<<< orphan*/ ,int) ; 
 struct mdp4_dtv_encoder* to_mdp4_dtv_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void mdp4_dtv_encoder_mode_set(struct drm_encoder *encoder,
		struct drm_display_mode *mode,
		struct drm_display_mode *adjusted_mode)
{
	struct mdp4_dtv_encoder *mdp4_dtv_encoder = to_mdp4_dtv_encoder(encoder);
	struct mdp4_kms *mdp4_kms = get_kms(encoder);
	uint32_t dtv_hsync_skew, vsync_period, vsync_len, ctrl_pol;
	uint32_t display_v_start, display_v_end;
	uint32_t hsync_start_x, hsync_end_x;

	mode = adjusted_mode;

	DBG("set mode: %d:\"%s\" %d %d %d %d %d %d %d %d %d %d 0x%x 0x%x",
			mode->base.id, mode->name,
			mode->vrefresh, mode->clock,
			mode->hdisplay, mode->hsync_start,
			mode->hsync_end, mode->htotal,
			mode->vdisplay, mode->vsync_start,
			mode->vsync_end, mode->vtotal,
			mode->type, mode->flags);

	mdp4_dtv_encoder->pixclock = mode->clock * 1000;

	DBG("pixclock=%lu", mdp4_dtv_encoder->pixclock);

	ctrl_pol = 0;
	if (mode->flags & DRM_MODE_FLAG_NHSYNC)
		ctrl_pol |= MDP4_DTV_CTRL_POLARITY_HSYNC_LOW;
	if (mode->flags & DRM_MODE_FLAG_NVSYNC)
		ctrl_pol |= MDP4_DTV_CTRL_POLARITY_VSYNC_LOW;
	/* probably need to get DATA_EN polarity from panel.. */

	dtv_hsync_skew = 0;  /* get this from panel? */

	hsync_start_x = (mode->htotal - mode->hsync_start);
	hsync_end_x = mode->htotal - (mode->hsync_start - mode->hdisplay) - 1;

	vsync_period = mode->vtotal * mode->htotal;
	vsync_len = (mode->vsync_end - mode->vsync_start) * mode->htotal;
	display_v_start = (mode->vtotal - mode->vsync_start) * mode->htotal + dtv_hsync_skew;
	display_v_end = vsync_period - ((mode->vsync_start - mode->vdisplay) * mode->htotal) + dtv_hsync_skew - 1;

	mdp4_write(mdp4_kms, REG_MDP4_DTV_HSYNC_CTRL,
			MDP4_DTV_HSYNC_CTRL_PULSEW(mode->hsync_end - mode->hsync_start) |
			MDP4_DTV_HSYNC_CTRL_PERIOD(mode->htotal));
	mdp4_write(mdp4_kms, REG_MDP4_DTV_VSYNC_PERIOD, vsync_period);
	mdp4_write(mdp4_kms, REG_MDP4_DTV_VSYNC_LEN, vsync_len);
	mdp4_write(mdp4_kms, REG_MDP4_DTV_DISPLAY_HCTRL,
			MDP4_DTV_DISPLAY_HCTRL_START(hsync_start_x) |
			MDP4_DTV_DISPLAY_HCTRL_END(hsync_end_x));
	mdp4_write(mdp4_kms, REG_MDP4_DTV_DISPLAY_VSTART, display_v_start);
	mdp4_write(mdp4_kms, REG_MDP4_DTV_DISPLAY_VEND, display_v_end);
	mdp4_write(mdp4_kms, REG_MDP4_DTV_BORDER_CLR, 0);
	mdp4_write(mdp4_kms, REG_MDP4_DTV_UNDERFLOW_CLR,
			MDP4_DTV_UNDERFLOW_CLR_ENABLE_RECOVERY |
			MDP4_DTV_UNDERFLOW_CLR_COLOR(0xff));
	mdp4_write(mdp4_kms, REG_MDP4_DTV_HSYNC_SKEW, dtv_hsync_skew);
	mdp4_write(mdp4_kms, REG_MDP4_DTV_CTRL_POLARITY, ctrl_pol);
	mdp4_write(mdp4_kms, REG_MDP4_DTV_ACTIVE_HCTL,
			MDP4_DTV_ACTIVE_HCTL_START(0) |
			MDP4_DTV_ACTIVE_HCTL_END(0));
	mdp4_write(mdp4_kms, REG_MDP4_DTV_ACTIVE_VSTART, 0);
	mdp4_write(mdp4_kms, REG_MDP4_DTV_ACTIVE_VEND, 0);
}