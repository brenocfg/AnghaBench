#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct mdp5_kms {int dummy; } ;
struct TYPE_5__ {TYPE_1__* mixer; } ;
struct mdp5_crtc_state {TYPE_2__ pipeline; } ;
struct TYPE_6__ {int x; int y; int width; int height; int iova; int /*<<< orphan*/  lock; } ;
struct mdp5_crtc {TYPE_3__ cursor; } ;
struct drm_format_info {int* cpp; } ;
struct drm_crtc {int /*<<< orphan*/  name; int /*<<< orphan*/  state; } ;
typedef  enum mdp5_cursor_alpha { ____Placeholder_mdp5_cursor_alpha } mdp5_cursor_alpha ;
struct TYPE_4__ {int lm; } ;

/* Variables and functions */
 int CURSOR_ALPHA_PER_PIXEL ; 
 int /*<<< orphan*/  CURSOR_FMT_ARGB8888 ; 
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  DRM_FORMAT_ARGB8888 ; 
 int MDP5_LM_CURSOR_BLEND_CONFIG_BLEND_ALPHA_SEL (int const) ; 
 int MDP5_LM_CURSOR_BLEND_CONFIG_BLEND_EN ; 
 int MDP5_LM_CURSOR_FORMAT_FORMAT (int /*<<< orphan*/ ) ; 
 int MDP5_LM_CURSOR_IMG_SIZE_SRC_H (int) ; 
 int MDP5_LM_CURSOR_IMG_SIZE_SRC_W (int) ; 
 int MDP5_LM_CURSOR_SIZE_ROI_H (int) ; 
 int MDP5_LM_CURSOR_SIZE_ROI_W (int) ; 
 int MDP5_LM_CURSOR_START_XY_X_START (int) ; 
 int MDP5_LM_CURSOR_START_XY_Y_START (int) ; 
 int MDP5_LM_CURSOR_XY_SRC_X (int) ; 
 int MDP5_LM_CURSOR_XY_SRC_Y (int) ; 
 int /*<<< orphan*/  REG_MDP5_LM_CURSOR_BASE_ADDR (int) ; 
 int /*<<< orphan*/  REG_MDP5_LM_CURSOR_BLEND_CONFIG (int) ; 
 int /*<<< orphan*/  REG_MDP5_LM_CURSOR_FORMAT (int) ; 
 int /*<<< orphan*/  REG_MDP5_LM_CURSOR_IMG_SIZE (int) ; 
 int /*<<< orphan*/  REG_MDP5_LM_CURSOR_SIZE (int) ; 
 int /*<<< orphan*/  REG_MDP5_LM_CURSOR_START_XY (int) ; 
 int /*<<< orphan*/  REG_MDP5_LM_CURSOR_STRIDE (int) ; 
 int /*<<< orphan*/  REG_MDP5_LM_CURSOR_XY (int) ; 
 int abs (scalar_t__) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 struct drm_format_info* drm_format_info (int /*<<< orphan*/ ) ; 
 struct mdp5_kms* get_kms (struct drm_crtc*) ; 
 int /*<<< orphan*/  get_roi (struct drm_crtc*,int*,int*) ; 
 int /*<<< orphan*/  mdp5_write (struct mdp5_kms*,int /*<<< orphan*/ ,int) ; 
 struct mdp5_crtc* to_mdp5_crtc (struct drm_crtc*) ; 
 struct mdp5_crtc_state* to_mdp5_crtc_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mdp5_crtc_restore_cursor(struct drm_crtc *crtc)
{
	const struct drm_format_info *info = drm_format_info(DRM_FORMAT_ARGB8888);
	struct mdp5_crtc_state *mdp5_cstate = to_mdp5_crtc_state(crtc->state);
	struct mdp5_crtc *mdp5_crtc = to_mdp5_crtc(crtc);
	struct mdp5_kms *mdp5_kms = get_kms(crtc);
	const enum mdp5_cursor_alpha cur_alpha = CURSOR_ALPHA_PER_PIXEL;
	uint32_t blendcfg, stride;
	uint32_t x, y, src_x, src_y, width, height;
	uint32_t roi_w, roi_h;
	int lm;

	assert_spin_locked(&mdp5_crtc->cursor.lock);

	lm = mdp5_cstate->pipeline.mixer->lm;

	x = mdp5_crtc->cursor.x;
	y = mdp5_crtc->cursor.y;
	width = mdp5_crtc->cursor.width;
	height = mdp5_crtc->cursor.height;

	stride = width * info->cpp[0];

	get_roi(crtc, &roi_w, &roi_h);

	/* If cusror buffer overlaps due to rotation on the
	 * upper or left screen border the pixel offset inside
	 * the cursor buffer of the ROI is the positive overlap
	 * distance.
	 */
	if (mdp5_crtc->cursor.x < 0) {
		src_x = abs(mdp5_crtc->cursor.x);
		x = 0;
	} else {
		src_x = 0;
	}
	if (mdp5_crtc->cursor.y < 0) {
		src_y = abs(mdp5_crtc->cursor.y);
		y = 0;
	} else {
		src_y = 0;
	}
	DBG("%s: x=%d, y=%d roi_w=%d roi_h=%d src_x=%d src_y=%d",
		crtc->name, x, y, roi_w, roi_h, src_x, src_y);

	mdp5_write(mdp5_kms, REG_MDP5_LM_CURSOR_STRIDE(lm), stride);
	mdp5_write(mdp5_kms, REG_MDP5_LM_CURSOR_FORMAT(lm),
			MDP5_LM_CURSOR_FORMAT_FORMAT(CURSOR_FMT_ARGB8888));
	mdp5_write(mdp5_kms, REG_MDP5_LM_CURSOR_IMG_SIZE(lm),
			MDP5_LM_CURSOR_IMG_SIZE_SRC_H(height) |
			MDP5_LM_CURSOR_IMG_SIZE_SRC_W(width));
	mdp5_write(mdp5_kms, REG_MDP5_LM_CURSOR_SIZE(lm),
			MDP5_LM_CURSOR_SIZE_ROI_H(roi_h) |
			MDP5_LM_CURSOR_SIZE_ROI_W(roi_w));
	mdp5_write(mdp5_kms, REG_MDP5_LM_CURSOR_START_XY(lm),
			MDP5_LM_CURSOR_START_XY_Y_START(y) |
			MDP5_LM_CURSOR_START_XY_X_START(x));
	mdp5_write(mdp5_kms, REG_MDP5_LM_CURSOR_XY(lm),
			MDP5_LM_CURSOR_XY_SRC_Y(src_y) |
			MDP5_LM_CURSOR_XY_SRC_X(src_x));
	mdp5_write(mdp5_kms, REG_MDP5_LM_CURSOR_BASE_ADDR(lm),
			mdp5_crtc->cursor.iova);

	blendcfg = MDP5_LM_CURSOR_BLEND_CONFIG_BLEND_EN;
	blendcfg |= MDP5_LM_CURSOR_BLEND_CONFIG_BLEND_ALPHA_SEL(cur_alpha);
	mdp5_write(mdp5_kms, REG_MDP5_LM_CURSOR_BLEND_CONFIG(lm), blendcfg);
}