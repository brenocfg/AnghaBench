#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int u64 ;
typedef  int u32 ;
struct vc4_plane_state {int dlist_count; int dlist_initialized; int src_y; int* src_h; int* offsets; int src_x; int pos0_offset; int crtc_x; int crtc_y; int crtc_w; int crtc_h; int pos2_offset; int* src_w; int ptr0_offset; scalar_t__* x_scaling; scalar_t__* y_scaling; int* dlist; int needs_bg_fill; scalar_t__ lbm_offset; scalar_t__ is_yuv; scalar_t__ is_unity; } ;
struct vc4_dev {TYPE_2__* hvs; } ;
struct hvs_format {int hvs; int pixel_order; } ;
struct drm_plane_state {int alpha; TYPE_4__* crtc; int /*<<< orphan*/  rotation; struct drm_framebuffer* fb; } ;
struct drm_plane {int /*<<< orphan*/  dev; } ;
struct drm_framebuffer {int* pitches; TYPE_5__* format; scalar_t__ modifier; } ;
struct TYPE_10__ {int num_planes; int hsub; int vsub; int* cpp; scalar_t__ has_alpha; int /*<<< orphan*/  format; } ;
struct TYPE_8__ {int hdisplay; int vdisplay; } ;
struct TYPE_9__ {TYPE_3__ mode; } ;
struct TYPE_6__ {int start; } ;
struct TYPE_7__ {TYPE_1__ mitchell_netravali_filter; } ;

/* Variables and functions */
 int DRM_BLEND_ALPHA_OPAQUE ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,long long) ; 
#define  DRM_FORMAT_MOD_BROADCOM_SAND128 132 
#define  DRM_FORMAT_MOD_BROADCOM_SAND256 131 
#define  DRM_FORMAT_MOD_BROADCOM_SAND64 130 
#define  DRM_FORMAT_MOD_BROADCOM_VC4_T_TILED 129 
#define  DRM_FORMAT_MOD_LINEAR 128 
 unsigned int DRM_MODE_REFLECT_X ; 
 unsigned int DRM_MODE_REFLECT_Y ; 
 unsigned int DRM_MODE_ROTATE_0 ; 
 int EINVAL ; 
 int HVS_PIXEL_FORMAT_H264 ; 
 int SCALER_CSC0_ITR_R_601_5 ; 
 int SCALER_CSC1_ITR_R_601_5 ; 
 int SCALER_CSC2_ITR_R_601_5 ; 
 int SCALER_CTL0_HFLIP ; 
 int SCALER_CTL0_ORDER_SHIFT ; 
 int SCALER_CTL0_PIXEL_FORMAT_SHIFT ; 
 int /*<<< orphan*/  SCALER_CTL0_RGBA_EXPAND ; 
 int SCALER_CTL0_RGBA_EXPAND_ROUND ; 
 int /*<<< orphan*/  SCALER_CTL0_SCL0 ; 
 int /*<<< orphan*/  SCALER_CTL0_SCL1 ; 
 int /*<<< orphan*/  SCALER_CTL0_SIZE ; 
 int /*<<< orphan*/  SCALER_CTL0_TILING ; 
 int SCALER_CTL0_TILING_128B ; 
 int SCALER_CTL0_TILING_256B_OR_T ; 
 int SCALER_CTL0_TILING_64B ; 
 int SCALER_CTL0_TILING_LINEAR ; 
 int SCALER_CTL0_UNITY ; 
 int SCALER_CTL0_VALID ; 
 int SCALER_CTL0_VFLIP ; 
 int /*<<< orphan*/  SCALER_PITCH0_SINK_PIX ; 
 int SCALER_PITCH0_TILE_INITIAL_LINE_DIR ; 
 int SCALER_PITCH0_TILE_LINE_DIR ; 
 int /*<<< orphan*/  SCALER_PITCH0_TILE_WIDTH_L ; 
 int /*<<< orphan*/  SCALER_PITCH0_TILE_WIDTH_R ; 
 int /*<<< orphan*/  SCALER_PITCH0_TILE_Y_OFFSET ; 
 int /*<<< orphan*/  SCALER_POS0_FIXED_ALPHA ; 
 int /*<<< orphan*/  SCALER_POS0_START_X ; 
 int /*<<< orphan*/  SCALER_POS0_START_Y ; 
 int /*<<< orphan*/  SCALER_POS1_SCL_HEIGHT ; 
 int /*<<< orphan*/  SCALER_POS1_SCL_WIDTH ; 
 int SCALER_POS2_ALPHA_MIX ; 
 int /*<<< orphan*/  SCALER_POS2_ALPHA_MODE ; 
 int SCALER_POS2_ALPHA_MODE_FIXED ; 
 int SCALER_POS2_ALPHA_MODE_PIPELINE ; 
 int SCALER_POS2_ALPHA_PREMULT ; 
 int /*<<< orphan*/  SCALER_POS2_HEIGHT ; 
 int /*<<< orphan*/  SCALER_POS2_WIDTH ; 
 int /*<<< orphan*/  SCALER_PPF_KERNEL_OFFSET ; 
 int /*<<< orphan*/  SCALER_SRC_PITCH ; 
 int /*<<< orphan*/  SCALER_TILE_HEIGHT ; 
 int SCALER_TILE_HEIGHT_MASK ; 
 scalar_t__ VC4_SCALING_NONE ; 
 scalar_t__ VC4_SCALING_PPF ; 
 int VC4_SET_FIELD (int,int /*<<< orphan*/ ) ; 
 unsigned int drm_rotation_simplify (int /*<<< orphan*/ ,unsigned int) ; 
 int fourcc_mod_broadcom_mod (scalar_t__) ; 
 int fourcc_mod_broadcom_param (scalar_t__) ; 
 struct vc4_dev* to_vc4_dev (int /*<<< orphan*/ ) ; 
 struct vc4_plane_state* to_vc4_plane_state (struct drm_plane_state*) ; 
 int /*<<< orphan*/  vc4_dlist_write (struct vc4_plane_state*,int) ; 
 struct hvs_format* vc4_get_hvs_format (int /*<<< orphan*/ ) ; 
 int vc4_get_scl_field (struct drm_plane_state*,int) ; 
 int /*<<< orphan*/  vc4_plane_calc_load (struct drm_plane_state*) ; 
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
	int num_planes = fb->format->num_planes;
	u32 h_subsample = fb->format->hsub;
	u32 v_subsample = fb->format->vsub;
	bool mix_plane_alpha;
	bool covers_screen;
	u32 scl0, scl1, pitch0;
	u32 tiling, src_y;
	u32 hvs_format = format->hvs;
	unsigned int rotation;
	int ret, i;

	if (vc4_state->dlist_initialized)
		return 0;

	ret = vc4_plane_setup_clipping_and_scaling(state);
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

	rotation = drm_rotation_simplify(state->rotation,
					 DRM_MODE_ROTATE_0 |
					 DRM_MODE_REFLECT_X |
					 DRM_MODE_REFLECT_Y);

	/* We must point to the last line when Y reflection is enabled. */
	src_y = vc4_state->src_y;
	if (rotation & DRM_MODE_REFLECT_Y)
		src_y += vc4_state->src_h[0] - 1;

	switch (base_format_mod) {
	case DRM_FORMAT_MOD_LINEAR:
		tiling = SCALER_CTL0_TILING_LINEAR;
		pitch0 = VC4_SET_FIELD(fb->pitches[0], SCALER_SRC_PITCH);

		/* Adjust the base pointer to the first pixel to be scanned
		 * out.
		 */
		for (i = 0; i < num_planes; i++) {
			vc4_state->offsets[i] += src_y /
						 (i ? v_subsample : 1) *
						 fb->pitches[i];

			vc4_state->offsets[i] += vc4_state->src_x /
						 (i ? h_subsample : 1) *
						 fb->format->cpp[i];
		}

		break;

	case DRM_FORMAT_MOD_BROADCOM_VC4_T_TILED: {
		u32 tile_size_shift = 12; /* T tiles are 4kb */
		/* Whole-tile offsets, mostly for setting the pitch. */
		u32 tile_w_shift = fb->format->cpp[0] == 2 ? 6 : 5;
		u32 tile_h_shift = 5; /* 16 and 32bpp are 32 pixels high */
		u32 tile_w_mask = (1 << tile_w_shift) - 1;
		/* The height mask on 32-bit-per-pixel tiles is 63, i.e. twice
		 * the height (in pixels) of a 4k tile.
		 */
		u32 tile_h_mask = (2 << tile_h_shift) - 1;
		/* For T-tiled, the FB pitch is "how many bytes from one row to
		 * the next, such that
		 *
		 *	pitch * tile_h == tile_size * tiles_per_row
		 */
		u32 tiles_w = fb->pitches[0] >> (tile_size_shift - tile_h_shift);
		u32 tiles_l = vc4_state->src_x >> tile_w_shift;
		u32 tiles_r = tiles_w - tiles_l;
		u32 tiles_t = src_y >> tile_h_shift;
		/* Intra-tile offsets, which modify the base address (the
		 * SCALER_PITCH0_TILE_Y_OFFSET tells HVS how to walk from that
		 * base address).
		 */
		u32 tile_y = (src_y >> 4) & 1;
		u32 subtile_y = (src_y >> 2) & 3;
		u32 utile_y = src_y & 3;
		u32 x_off = vc4_state->src_x & tile_w_mask;
		u32 y_off = src_y & tile_h_mask;

		/* When Y reflection is requested we must set the
		 * SCALER_PITCH0_TILE_LINE_DIR flag to tell HVS that all lines
		 * after the initial one should be fetched in descending order,
		 * which makes sense since we start from the last line and go
		 * backward.
		 * Don't know why we need y_off = max_y_off - y_off, but it's
		 * definitely required (I guess it's also related to the "going
		 * backward" situation).
		 */
		if (rotation & DRM_MODE_REFLECT_Y) {
			y_off = tile_h_mask - y_off;
			pitch0 = SCALER_PITCH0_TILE_LINE_DIR;
		} else {
			pitch0 = 0;
		}

		tiling = SCALER_CTL0_TILING_256B_OR_T;
		pitch0 |= (VC4_SET_FIELD(x_off, SCALER_PITCH0_SINK_PIX) |
			   VC4_SET_FIELD(y_off, SCALER_PITCH0_TILE_Y_OFFSET) |
			   VC4_SET_FIELD(tiles_l, SCALER_PITCH0_TILE_WIDTH_L) |
			   VC4_SET_FIELD(tiles_r, SCALER_PITCH0_TILE_WIDTH_R));
		vc4_state->offsets[0] += tiles_t * (tiles_w << tile_size_shift);
		vc4_state->offsets[0] += subtile_y << 8;
		vc4_state->offsets[0] += utile_y << 4;

		/* Rows of tiles alternate left-to-right and right-to-left. */
		if (tiles_t & 1) {
			pitch0 |= SCALER_PITCH0_TILE_INITIAL_LINE_DIR;
			vc4_state->offsets[0] += (tiles_w - tiles_l) <<
						 tile_size_shift;
			vc4_state->offsets[0] -= (1 + !tile_y) << 10;
		} else {
			vc4_state->offsets[0] += tiles_l << tile_size_shift;
			vc4_state->offsets[0] += tile_y << 10;
		}

		break;
	}

	case DRM_FORMAT_MOD_BROADCOM_SAND64:
	case DRM_FORMAT_MOD_BROADCOM_SAND128:
	case DRM_FORMAT_MOD_BROADCOM_SAND256: {
		uint32_t param = fourcc_mod_broadcom_param(fb->modifier);
		u32 tile_w, tile, x_off, pix_per_tile;

		hvs_format = HVS_PIXEL_FORMAT_H264;

		switch (base_format_mod) {
		case DRM_FORMAT_MOD_BROADCOM_SAND64:
			tiling = SCALER_CTL0_TILING_64B;
			tile_w = 64;
			break;
		case DRM_FORMAT_MOD_BROADCOM_SAND128:
			tiling = SCALER_CTL0_TILING_128B;
			tile_w = 128;
			break;
		case DRM_FORMAT_MOD_BROADCOM_SAND256:
			tiling = SCALER_CTL0_TILING_256B_OR_T;
			tile_w = 256;
			break;
		default:
			break;
		}

		if (param > SCALER_TILE_HEIGHT_MASK) {
			DRM_DEBUG_KMS("SAND height too large (%d)\n", param);
			return -EINVAL;
		}

		pix_per_tile = tile_w / fb->format->cpp[0];
		tile = vc4_state->src_x / pix_per_tile;
		x_off = vc4_state->src_x % pix_per_tile;

		/* Adjust the base pointer to the first pixel to be scanned
		 * out.
		 */
		for (i = 0; i < num_planes; i++) {
			vc4_state->offsets[i] += param * tile_w * tile;
			vc4_state->offsets[i] += src_y /
						 (i ? v_subsample : 1) *
						 tile_w;
			vc4_state->offsets[i] += x_off /
						 (i ? h_subsample : 1) *
						 fb->format->cpp[i];
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
			(rotation & DRM_MODE_REFLECT_X ? SCALER_CTL0_HFLIP : 0) |
			(rotation & DRM_MODE_REFLECT_Y ? SCALER_CTL0_VFLIP : 0) |
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

	vc4_state->lbm_offset = 0;

	if (vc4_state->x_scaling[0] != VC4_SCALING_NONE ||
	    vc4_state->x_scaling[1] != VC4_SCALING_NONE ||
	    vc4_state->y_scaling[0] != VC4_SCALING_NONE ||
	    vc4_state->y_scaling[1] != VC4_SCALING_NONE) {
		/* Reserve a slot for the LBM Base Address. The real value will
		 * be set when calling vc4_plane_allocate_lbm().
		 */
		if (vc4_state->y_scaling[0] != VC4_SCALING_NONE ||
		    vc4_state->y_scaling[1] != VC4_SCALING_NONE)
			vc4_state->lbm_offset = vc4_state->dlist_count++;

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

	/* Flag the dlist as initialized to avoid checking it twice in case
	 * the async update check already called vc4_plane_mode_set() and
	 * decided to fallback to sync update because async update was not
	 * possible.
	 */
	vc4_state->dlist_initialized = 1;

	vc4_plane_calc_load(state);

	return 0;
}