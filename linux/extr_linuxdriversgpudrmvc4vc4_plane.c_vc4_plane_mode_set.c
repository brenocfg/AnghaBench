#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_12__ {scalar_t__ size; scalar_t__ start; int /*<<< orphan*/  allocated; } ;
struct vc4_plane_state {scalar_t__ dlist_count; scalar_t__ pos0_offset; int crtc_x; int crtc_y; int crtc_w; int crtc_h; scalar_t__ pos2_offset; int* src_w; int* src_h; scalar_t__ ptr0_offset; scalar_t__* offsets; scalar_t__* x_scaling; scalar_t__* y_scaling; scalar_t__* dlist; int needs_bg_fill; TYPE_6__ lbm; scalar_t__ is_yuv; scalar_t__ is_unity; } ;
struct vc4_dev {TYPE_4__* hvs; } ;
struct hvs_format {scalar_t__ hvs; scalar_t__ pixel_order; int /*<<< orphan*/  drm; } ;
struct drm_plane_state {int alpha; TYPE_3__* crtc; struct drm_framebuffer* fb; } ;
struct drm_plane {int /*<<< orphan*/  dev; } ;
struct drm_framebuffer {int* pitches; TYPE_5__* format; scalar_t__ modifier; } ;
struct TYPE_11__ {int num_planes; scalar_t__ has_alpha; int /*<<< orphan*/  format; } ;
struct TYPE_7__ {int start; } ;
struct TYPE_10__ {TYPE_1__ mitchell_netravali_filter; int /*<<< orphan*/  mm_lock; int /*<<< orphan*/  lbm_mm; } ;
struct TYPE_8__ {int hdisplay; int vdisplay; } ;
struct TYPE_9__ {TYPE_2__ mode; } ;

/* Variables and functions */
 int DRM_BLEND_ALPHA_OPAQUE ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
#define  DRM_FORMAT_MOD_BROADCOM_SAND128 132 
#define  DRM_FORMAT_MOD_BROADCOM_SAND256 131 
#define  DRM_FORMAT_MOD_BROADCOM_SAND64 130 
#define  DRM_FORMAT_MOD_BROADCOM_VC4_T_TILED 129 
#define  DRM_FORMAT_MOD_LINEAR 128 
 int EINVAL ; 
 scalar_t__ HVS_PIXEL_FORMAT_H264 ; 
 scalar_t__ HVS_PIXEL_FORMAT_YCBCR_YUV420_2PLANE ; 
 scalar_t__ SCALER_CSC0_ITR_R_601_5 ; 
 scalar_t__ SCALER_CSC1_ITR_R_601_5 ; 
 scalar_t__ SCALER_CSC2_ITR_R_601_5 ; 
 scalar_t__ SCALER_CTL0_ORDER_SHIFT ; 
 scalar_t__ SCALER_CTL0_PIXEL_FORMAT_SHIFT ; 
 int /*<<< orphan*/  SCALER_CTL0_RGBA_EXPAND ; 
 int SCALER_CTL0_RGBA_EXPAND_ROUND ; 
 int /*<<< orphan*/  SCALER_CTL0_SCL0 ; 
 int /*<<< orphan*/  SCALER_CTL0_SCL1 ; 
 int /*<<< orphan*/  SCALER_CTL0_SIZE ; 
 int /*<<< orphan*/  SCALER_CTL0_TILING ; 
 scalar_t__ SCALER_CTL0_TILING_128B ; 
 scalar_t__ SCALER_CTL0_TILING_256B_OR_T ; 
 scalar_t__ SCALER_CTL0_TILING_64B ; 
 scalar_t__ SCALER_CTL0_TILING_LINEAR ; 
 scalar_t__ SCALER_CTL0_UNITY ; 
 scalar_t__ SCALER_CTL0_VALID ; 
 int /*<<< orphan*/  SCALER_PITCH0_TILE_WIDTH_L ; 
 int /*<<< orphan*/  SCALER_PITCH0_TILE_WIDTH_R ; 
 int /*<<< orphan*/  SCALER_PITCH0_TILE_Y_OFFSET ; 
 int /*<<< orphan*/  SCALER_POS0_FIXED_ALPHA ; 
 int /*<<< orphan*/  SCALER_POS0_START_X ; 
 int /*<<< orphan*/  SCALER_POS0_START_Y ; 
 int /*<<< orphan*/  SCALER_POS1_SCL_HEIGHT ; 
 int /*<<< orphan*/  SCALER_POS1_SCL_WIDTH ; 
 scalar_t__ SCALER_POS2_ALPHA_MIX ; 
 int /*<<< orphan*/  SCALER_POS2_ALPHA_MODE ; 
 int SCALER_POS2_ALPHA_MODE_FIXED ; 
 int SCALER_POS2_ALPHA_MODE_PIPELINE ; 
 scalar_t__ SCALER_POS2_ALPHA_PREMULT ; 
 int /*<<< orphan*/  SCALER_POS2_HEIGHT ; 
 int /*<<< orphan*/  SCALER_POS2_WIDTH ; 
 int /*<<< orphan*/  SCALER_PPF_KERNEL_OFFSET ; 
 int /*<<< orphan*/  SCALER_SRC_PITCH ; 
 int /*<<< orphan*/  SCALER_TILE_HEIGHT ; 
 int SCALER_TILE_HEIGHT_MASK ; 
 scalar_t__ VC4_SCALING_NONE ; 
 scalar_t__ VC4_SCALING_PPF ; 
 scalar_t__ VC4_SET_FIELD (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int drm_format_num_planes (int /*<<< orphan*/ ) ; 
 int drm_mm_insert_node_generic (int /*<<< orphan*/ *,TYPE_6__*,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fourcc_mod_broadcom_mod (scalar_t__) ; 
 int fourcc_mod_broadcom_param (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vc4_dev* to_vc4_dev (int /*<<< orphan*/ ) ; 
 struct vc4_plane_state* to_vc4_plane_state (struct drm_plane_state*) ; 
 int /*<<< orphan*/  vc4_dlist_write (struct vc4_plane_state*,scalar_t__) ; 
 struct hvs_format* vc4_get_hvs_format (int /*<<< orphan*/ ) ; 
 scalar_t__ vc4_get_scl_field (struct drm_plane_state*,int) ; 
 scalar_t__ vc4_lbm_size (struct drm_plane_state*) ; 
 int vc4_plane_setup_clipping_and_scaling (struct drm_plane_state*) ; 
 int /*<<< orphan*/  vc4_write_scaling_parameters (struct drm_plane_state*,int) ; 

__attribute__((used)) static int vc4_plane_mode_set(struct drm_plane *plane,
			      struct drm_plane_state *state)
{
	struct vc4_dev *vc4 = to_vc4_dev(plane->dev);
	struct vc4_plane_state *vc4_state = to_vc4_plane_state(state);
	struct drm_framebuffer *fb = state->fb;
	u32 ctl0_offset = vc4_state->dlist_count;
	const struct hvs_format *format = vc4_get_hvs_format(fb->format->format);
	u64 base_format_mod = fourcc_mod_broadcom_mod(fb->modifier);
	int num_planes = drm_format_num_planes(format->drm);
	bool mix_plane_alpha;
	bool covers_screen;
	u32 scl0, scl1, pitch0;
	u32 lbm_size, tiling;
	unsigned long irqflags;
	u32 hvs_format = format->hvs;
	int ret, i;

	ret = vc4_plane_setup_clipping_and_scaling(state);
	if (ret)
		return ret;

	/* Allocate the LBM memory that the HVS will use for temporary
	 * storage due to our scaling/format conversion.
	 */
	lbm_size = vc4_lbm_size(state);
	if (lbm_size) {
		if (!vc4_state->lbm.allocated) {
			spin_lock_irqsave(&vc4->hvs->mm_lock, irqflags);
			ret = drm_mm_insert_node_generic(&vc4->hvs->lbm_mm,
							 &vc4_state->lbm,
							 lbm_size, 32, 0, 0);
			spin_unlock_irqrestore(&vc4->hvs->mm_lock, irqflags);
		} else {
			WARN_ON_ONCE(lbm_size != vc4_state->lbm.size);
		}
	}

	if (ret)
		return ret;

	/* SCL1 is used for Cb/Cr scaling of planar formats.  For RGB
	 * and 4:4:4, scl1 should be set to scl0 so both channels of
	 * the scaler do the same thing.  For YUV, the Y plane needs
	 * to be put in channel 1 and Cb/Cr in channel 0, so we swap
	 * the scl fields here.
	 */
	if (num_planes == 1) {
		scl0 = vc4_get_scl_field(state, 0);
		scl1 = scl0;
	} else {
		scl0 = vc4_get_scl_field(state, 1);
		scl1 = vc4_get_scl_field(state, 0);
	}

	switch (base_format_mod) {
	case DRM_FORMAT_MOD_LINEAR:
		tiling = SCALER_CTL0_TILING_LINEAR;
		pitch0 = VC4_SET_FIELD(fb->pitches[0], SCALER_SRC_PITCH);
		break;

	case DRM_FORMAT_MOD_BROADCOM_VC4_T_TILED: {
		/* For T-tiled, the FB pitch is "how many bytes from
		 * one row to the next, such that pitch * tile_h ==
		 * tile_size * tiles_per_row."
		 */
		u32 tile_size_shift = 12; /* T tiles are 4kb */
		u32 tile_h_shift = 5; /* 16 and 32bpp are 32 pixels high */
		u32 tiles_w = fb->pitches[0] >> (tile_size_shift - tile_h_shift);

		tiling = SCALER_CTL0_TILING_256B_OR_T;

		pitch0 = (VC4_SET_FIELD(0, SCALER_PITCH0_TILE_Y_OFFSET) |
			  VC4_SET_FIELD(0, SCALER_PITCH0_TILE_WIDTH_L) |
			  VC4_SET_FIELD(tiles_w, SCALER_PITCH0_TILE_WIDTH_R));
		break;
	}

	case DRM_FORMAT_MOD_BROADCOM_SAND64:
	case DRM_FORMAT_MOD_BROADCOM_SAND128:
	case DRM_FORMAT_MOD_BROADCOM_SAND256: {
		uint32_t param = fourcc_mod_broadcom_param(fb->modifier);

		/* Column-based NV12 or RGBA.
		 */
		if (fb->format->num_planes > 1) {
			if (hvs_format != HVS_PIXEL_FORMAT_YCBCR_YUV420_2PLANE) {
				DRM_DEBUG_KMS("SAND format only valid for NV12/21");
				return -EINVAL;
			}
			hvs_format = HVS_PIXEL_FORMAT_H264;
		} else {
			if (base_format_mod == DRM_FORMAT_MOD_BROADCOM_SAND256) {
				DRM_DEBUG_KMS("SAND256 format only valid for H.264");
				return -EINVAL;
			}
		}

		switch (base_format_mod) {
		case DRM_FORMAT_MOD_BROADCOM_SAND64:
			tiling = SCALER_CTL0_TILING_64B;
			break;
		case DRM_FORMAT_MOD_BROADCOM_SAND128:
			tiling = SCALER_CTL0_TILING_128B;
			break;
		case DRM_FORMAT_MOD_BROADCOM_SAND256:
			tiling = SCALER_CTL0_TILING_256B_OR_T;
			break;
		default:
			break;
		}

		if (param > SCALER_TILE_HEIGHT_MASK) {
			DRM_DEBUG_KMS("SAND height too large (%d)\n", param);
			return -EINVAL;
		}

		pitch0 = VC4_SET_FIELD(param, SCALER_TILE_HEIGHT);
		break;
	}

	default:
		DRM_DEBUG_KMS("Unsupported FB tiling flag 0x%16llx",
			      (long long)fb->modifier);
		return -EINVAL;
	}

	/* Control word */
	vc4_dlist_write(vc4_state,
			SCALER_CTL0_VALID |
			VC4_SET_FIELD(SCALER_CTL0_RGBA_EXPAND_ROUND, SCALER_CTL0_RGBA_EXPAND) |
			(format->pixel_order << SCALER_CTL0_ORDER_SHIFT) |
			(hvs_format << SCALER_CTL0_PIXEL_FORMAT_SHIFT) |
			VC4_SET_FIELD(tiling, SCALER_CTL0_TILING) |
			(vc4_state->is_unity ? SCALER_CTL0_UNITY : 0) |
			VC4_SET_FIELD(scl0, SCALER_CTL0_SCL0) |
			VC4_SET_FIELD(scl1, SCALER_CTL0_SCL1));

	/* Position Word 0: Image Positions and Alpha Value */
	vc4_state->pos0_offset = vc4_state->dlist_count;
	vc4_dlist_write(vc4_state,
			VC4_SET_FIELD(state->alpha >> 8, SCALER_POS0_FIXED_ALPHA) |
			VC4_SET_FIELD(vc4_state->crtc_x, SCALER_POS0_START_X) |
			VC4_SET_FIELD(vc4_state->crtc_y, SCALER_POS0_START_Y));

	/* Position Word 1: Scaled Image Dimensions. */
	if (!vc4_state->is_unity) {
		vc4_dlist_write(vc4_state,
				VC4_SET_FIELD(vc4_state->crtc_w,
					      SCALER_POS1_SCL_WIDTH) |
				VC4_SET_FIELD(vc4_state->crtc_h,
					      SCALER_POS1_SCL_HEIGHT));
	}

	/* Don't waste cycles mixing with plane alpha if the set alpha
	 * is opaque or there is no per-pixel alpha information.
	 * In any case we use the alpha property value as the fixed alpha.
	 */
	mix_plane_alpha = state->alpha != DRM_BLEND_ALPHA_OPAQUE &&
			  fb->format->has_alpha;

	/* Position Word 2: Source Image Size, Alpha */
	vc4_state->pos2_offset = vc4_state->dlist_count;
	vc4_dlist_write(vc4_state,
			VC4_SET_FIELD(fb->format->has_alpha ?
				      SCALER_POS2_ALPHA_MODE_PIPELINE :
				      SCALER_POS2_ALPHA_MODE_FIXED,
				      SCALER_POS2_ALPHA_MODE) |
			(mix_plane_alpha ? SCALER_POS2_ALPHA_MIX : 0) |
			(fb->format->has_alpha ? SCALER_POS2_ALPHA_PREMULT : 0) |
			VC4_SET_FIELD(vc4_state->src_w[0], SCALER_POS2_WIDTH) |
			VC4_SET_FIELD(vc4_state->src_h[0], SCALER_POS2_HEIGHT));

	/* Position Word 3: Context.  Written by the HVS. */
	vc4_dlist_write(vc4_state, 0xc0c0c0c0);


	/* Pointer Word 0/1/2: RGB / Y / Cb / Cr Pointers
	 *
	 * The pointers may be any byte address.
	 */
	vc4_state->ptr0_offset = vc4_state->dlist_count;
	for (i = 0; i < num_planes; i++)
		vc4_dlist_write(vc4_state, vc4_state->offsets[i]);

	/* Pointer Context Word 0/1/2: Written by the HVS */
	for (i = 0; i < num_planes; i++)
		vc4_dlist_write(vc4_state, 0xc0c0c0c0);

	/* Pitch word 0 */
	vc4_dlist_write(vc4_state, pitch0);

	/* Pitch word 1/2 */
	for (i = 1; i < num_planes; i++) {
		if (hvs_format != HVS_PIXEL_FORMAT_H264) {
			vc4_dlist_write(vc4_state,
					VC4_SET_FIELD(fb->pitches[i],
						      SCALER_SRC_PITCH));
		} else {
			vc4_dlist_write(vc4_state, pitch0);
		}
	}

	/* Colorspace conversion words */
	if (vc4_state->is_yuv) {
		vc4_dlist_write(vc4_state, SCALER_CSC0_ITR_R_601_5);
		vc4_dlist_write(vc4_state, SCALER_CSC1_ITR_R_601_5);
		vc4_dlist_write(vc4_state, SCALER_CSC2_ITR_R_601_5);
	}

	if (vc4_state->x_scaling[0] != VC4_SCALING_NONE ||
	    vc4_state->x_scaling[1] != VC4_SCALING_NONE ||
	    vc4_state->y_scaling[0] != VC4_SCALING_NONE ||
	    vc4_state->y_scaling[1] != VC4_SCALING_NONE) {
		/* LBM Base Address. */
		if (vc4_state->y_scaling[0] != VC4_SCALING_NONE ||
		    vc4_state->y_scaling[1] != VC4_SCALING_NONE) {
			vc4_dlist_write(vc4_state, vc4_state->lbm.start);
		}

		if (num_planes > 1) {
			/* Emit Cb/Cr as channel 0 and Y as channel
			 * 1. This matches how we set up scl0/scl1
			 * above.
			 */
			vc4_write_scaling_parameters(state, 1);
		}
		vc4_write_scaling_parameters(state, 0);

		/* If any PPF setup was done, then all the kernel
		 * pointers get uploaded.
		 */
		if (vc4_state->x_scaling[0] == VC4_SCALING_PPF ||
		    vc4_state->y_scaling[0] == VC4_SCALING_PPF ||
		    vc4_state->x_scaling[1] == VC4_SCALING_PPF ||
		    vc4_state->y_scaling[1] == VC4_SCALING_PPF) {
			u32 kernel = VC4_SET_FIELD(vc4->hvs->mitchell_netravali_filter.start,
						   SCALER_PPF_KERNEL_OFFSET);

			/* HPPF plane 0 */
			vc4_dlist_write(vc4_state, kernel);
			/* VPPF plane 0 */
			vc4_dlist_write(vc4_state, kernel);
			/* HPPF plane 1 */
			vc4_dlist_write(vc4_state, kernel);
			/* VPPF plane 1 */
			vc4_dlist_write(vc4_state, kernel);
		}
	}

	vc4_state->dlist[ctl0_offset] |=
		VC4_SET_FIELD(vc4_state->dlist_count, SCALER_CTL0_SIZE);

	/* crtc_* are already clipped coordinates. */
	covers_screen = vc4_state->crtc_x == 0 && vc4_state->crtc_y == 0 &&
			vc4_state->crtc_w == state->crtc->mode.hdisplay &&
			vc4_state->crtc_h == state->crtc->mode.vdisplay;
	/* Background fill might be necessary when the plane has per-pixel
	 * alpha content or a non-opaque plane alpha and could blend from the
	 * background or does not cover the entire screen.
	 */
	vc4_state->needs_bg_fill = fb->format->has_alpha || !covers_screen ||
				   state->alpha != DRM_BLEND_ALPHA_OPAQUE;

	return 0;
}