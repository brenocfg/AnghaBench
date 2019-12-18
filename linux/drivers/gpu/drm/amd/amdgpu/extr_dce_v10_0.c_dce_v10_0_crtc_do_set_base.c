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
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
typedef  int u32 ;
struct drm_gem_object {int dummy; } ;
struct drm_framebuffer {int width; int height; int* pitches; struct drm_gem_object** obj; TYPE_3__* format; } ;
struct drm_format_name_buf {int dummy; } ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct TYPE_4__ {int hdisplay; int vdisplay; } ;
struct drm_crtc {TYPE_2__* primary; TYPE_1__ mode; struct drm_device* dev; } ;
struct amdgpu_device {int dummy; } ;
struct amdgpu_crtc {scalar_t__ crtc_offset; } ;
struct amdgpu_bo {int dummy; } ;
struct TYPE_6__ {int format; int* cpp; } ;
struct TYPE_5__ {struct drm_framebuffer* fb; } ;

/* Variables and functions */
 int ADDR_SURF_MICRO_TILING_DISPLAY ; 
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 
 int AMDGPU_TILING_GET (scalar_t__,int /*<<< orphan*/ ) ; 
 int ARRAY_1D_TILED_THIN1 ; 
 int ARRAY_2D_TILED_THIN1 ; 
 int /*<<< orphan*/  ARRAY_MODE ; 
 int /*<<< orphan*/  BANK_HEIGHT ; 
 int /*<<< orphan*/  BANK_WIDTH ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
#define  DRM_FORMAT_ABGR8888 143 
#define  DRM_FORMAT_ARGB1555 142 
#define  DRM_FORMAT_ARGB2101010 141 
#define  DRM_FORMAT_ARGB4444 140 
#define  DRM_FORMAT_ARGB8888 139 
#define  DRM_FORMAT_BGRA1010102 138 
#define  DRM_FORMAT_BGRA5551 137 
#define  DRM_FORMAT_BGRX1010102 136 
#define  DRM_FORMAT_BGRX5551 135 
#define  DRM_FORMAT_C8 134 
#define  DRM_FORMAT_RGB565 133 
#define  DRM_FORMAT_XBGR8888 132 
#define  DRM_FORMAT_XRGB1555 131 
#define  DRM_FORMAT_XRGB2101010 130 
#define  DRM_FORMAT_XRGB4444 129 
#define  DRM_FORMAT_XRGB8888 128 
 int EINVAL ; 
 int ENDIAN_8IN16 ; 
 int ENDIAN_8IN32 ; 
 int ENDIAN_NONE ; 
 int /*<<< orphan*/  GRPH_ARRAY_MODE ; 
 int /*<<< orphan*/  GRPH_BANK_HEIGHT ; 
 int /*<<< orphan*/  GRPH_BANK_WIDTH ; 
 int /*<<< orphan*/  GRPH_BLUE_CROSSBAR ; 
 int /*<<< orphan*/  GRPH_CONTROL ; 
 int /*<<< orphan*/  GRPH_DEPTH ; 
 int /*<<< orphan*/  GRPH_ENDIAN_SWAP ; 
 int /*<<< orphan*/  GRPH_FLIP_CONTROL ; 
 int /*<<< orphan*/  GRPH_FORMAT ; 
 int /*<<< orphan*/  GRPH_LUT_10BIT_BYPASS ; 
 int /*<<< orphan*/  GRPH_LUT_10BIT_BYPASS_EN ; 
 int /*<<< orphan*/  GRPH_MACRO_TILE_ASPECT ; 
 int /*<<< orphan*/  GRPH_MICRO_TILE_MODE ; 
 int /*<<< orphan*/  GRPH_NUM_BANKS ; 
 int /*<<< orphan*/  GRPH_PIPE_CONFIG ; 
 int GRPH_PRIMARY_SURFACE_ADDRESS__GRPH_PRIMARY_SURFACE_ADDRESS_MASK ; 
 int /*<<< orphan*/  GRPH_RED_CROSSBAR ; 
 int GRPH_SECONDARY_SURFACE_ADDRESS__GRPH_SECONDARY_SURFACE_ADDRESS_MASK ; 
 int /*<<< orphan*/  GRPH_SURFACE_UPDATE_H_RETRACE_EN ; 
 int /*<<< orphan*/  GRPH_SWAP_CNTL ; 
 int /*<<< orphan*/  GRPH_TILE_SPLIT ; 
 int /*<<< orphan*/  MACRO_TILE_ASPECT ; 
 int /*<<< orphan*/  NUM_BANKS ; 
 int /*<<< orphan*/  PIPE_CONFIG ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int RREG32 (scalar_t__) ; 
 int /*<<< orphan*/  TILE_SPLIT ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 
 int /*<<< orphan*/  amdgpu_bo_get_tiling_flags (struct amdgpu_bo*,scalar_t__*) ; 
 scalar_t__ amdgpu_bo_gpu_offset (struct amdgpu_bo*) ; 
 int amdgpu_bo_pin (struct amdgpu_bo*,int /*<<< orphan*/ ) ; 
 int amdgpu_bo_reserve (struct amdgpu_bo*,int) ; 
 int /*<<< orphan*/  amdgpu_bo_unpin (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  dce_v10_0_bandwidth_update (struct amdgpu_device*) ; 
 int /*<<< orphan*/  dce_v10_0_grph_enable (struct drm_crtc*,int) ; 
 int /*<<< orphan*/  dce_v10_0_vga_enable (struct drm_crtc*,int) ; 
 int /*<<< orphan*/  drm_get_format_name (int,struct drm_format_name_buf*) ; 
 struct amdgpu_bo* gem_to_amdgpu_bo (struct drm_gem_object*) ; 
 scalar_t__ mmGRPH_CONTROL ; 
 scalar_t__ mmGRPH_FLIP_CONTROL ; 
 scalar_t__ mmGRPH_LUT_10BIT_BYPASS ; 
 scalar_t__ mmGRPH_PITCH ; 
 scalar_t__ mmGRPH_PRIMARY_SURFACE_ADDRESS ; 
 scalar_t__ mmGRPH_PRIMARY_SURFACE_ADDRESS_HIGH ; 
 scalar_t__ mmGRPH_SECONDARY_SURFACE_ADDRESS ; 
 scalar_t__ mmGRPH_SECONDARY_SURFACE_ADDRESS_HIGH ; 
 scalar_t__ mmGRPH_SURFACE_OFFSET_X ; 
 scalar_t__ mmGRPH_SURFACE_OFFSET_Y ; 
 scalar_t__ mmGRPH_SWAP_CNTL ; 
 scalar_t__ mmGRPH_X_END ; 
 scalar_t__ mmGRPH_X_START ; 
 scalar_t__ mmGRPH_Y_END ; 
 scalar_t__ mmGRPH_Y_START ; 
 scalar_t__ mmLB_DESKTOP_HEIGHT ; 
 scalar_t__ mmMASTER_UPDATE_MODE ; 
 scalar_t__ mmVIEWPORT_SIZE ; 
 scalar_t__ mmVIEWPORT_START ; 
 struct amdgpu_crtc* to_amdgpu_crtc (struct drm_crtc*) ; 
 scalar_t__ unlikely (int) ; 
 int upper_32_bits (scalar_t__) ; 

__attribute__((used)) static int dce_v10_0_crtc_do_set_base(struct drm_crtc *crtc,
				     struct drm_framebuffer *fb,
				     int x, int y, int atomic)
{
	struct amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	struct drm_device *dev = crtc->dev;
	struct amdgpu_device *adev = dev->dev_private;
	struct drm_framebuffer *target_fb;
	struct drm_gem_object *obj;
	struct amdgpu_bo *abo;
	uint64_t fb_location, tiling_flags;
	uint32_t fb_format, fb_pitch_pixels;
	u32 fb_swap = REG_SET_FIELD(0, GRPH_SWAP_CNTL, GRPH_ENDIAN_SWAP, ENDIAN_NONE);
	u32 pipe_config;
	u32 tmp, viewport_w, viewport_h;
	int r;
	bool bypass_lut = false;
	struct drm_format_name_buf format_name;

	/* no fb bound */
	if (!atomic && !crtc->primary->fb) {
		DRM_DEBUG_KMS("No FB bound\n");
		return 0;
	}

	if (atomic)
		target_fb = fb;
	else
		target_fb = crtc->primary->fb;

	/* If atomic, assume fb object is pinned & idle & fenced and
	 * just update base pointers
	 */
	obj = target_fb->obj[0];
	abo = gem_to_amdgpu_bo(obj);
	r = amdgpu_bo_reserve(abo, false);
	if (unlikely(r != 0))
		return r;

	if (!atomic) {
		r = amdgpu_bo_pin(abo, AMDGPU_GEM_DOMAIN_VRAM);
		if (unlikely(r != 0)) {
			amdgpu_bo_unreserve(abo);
			return -EINVAL;
		}
	}
	fb_location = amdgpu_bo_gpu_offset(abo);

	amdgpu_bo_get_tiling_flags(abo, &tiling_flags);
	amdgpu_bo_unreserve(abo);

	pipe_config = AMDGPU_TILING_GET(tiling_flags, PIPE_CONFIG);

	switch (target_fb->format->format) {
	case DRM_FORMAT_C8:
		fb_format = REG_SET_FIELD(0, GRPH_CONTROL, GRPH_DEPTH, 0);
		fb_format = REG_SET_FIELD(fb_format, GRPH_CONTROL, GRPH_FORMAT, 0);
		break;
	case DRM_FORMAT_XRGB4444:
	case DRM_FORMAT_ARGB4444:
		fb_format = REG_SET_FIELD(0, GRPH_CONTROL, GRPH_DEPTH, 1);
		fb_format = REG_SET_FIELD(fb_format, GRPH_CONTROL, GRPH_FORMAT, 2);
#ifdef __BIG_ENDIAN
		fb_swap = REG_SET_FIELD(fb_swap, GRPH_SWAP_CNTL, GRPH_ENDIAN_SWAP,
					ENDIAN_8IN16);
#endif
		break;
	case DRM_FORMAT_XRGB1555:
	case DRM_FORMAT_ARGB1555:
		fb_format = REG_SET_FIELD(0, GRPH_CONTROL, GRPH_DEPTH, 1);
		fb_format = REG_SET_FIELD(fb_format, GRPH_CONTROL, GRPH_FORMAT, 0);
#ifdef __BIG_ENDIAN
		fb_swap = REG_SET_FIELD(fb_swap, GRPH_SWAP_CNTL, GRPH_ENDIAN_SWAP,
					ENDIAN_8IN16);
#endif
		break;
	case DRM_FORMAT_BGRX5551:
	case DRM_FORMAT_BGRA5551:
		fb_format = REG_SET_FIELD(0, GRPH_CONTROL, GRPH_DEPTH, 1);
		fb_format = REG_SET_FIELD(fb_format, GRPH_CONTROL, GRPH_FORMAT, 5);
#ifdef __BIG_ENDIAN
		fb_swap = REG_SET_FIELD(fb_swap, GRPH_SWAP_CNTL, GRPH_ENDIAN_SWAP,
					ENDIAN_8IN16);
#endif
		break;
	case DRM_FORMAT_RGB565:
		fb_format = REG_SET_FIELD(0, GRPH_CONTROL, GRPH_DEPTH, 1);
		fb_format = REG_SET_FIELD(fb_format, GRPH_CONTROL, GRPH_FORMAT, 1);
#ifdef __BIG_ENDIAN
		fb_swap = REG_SET_FIELD(fb_swap, GRPH_SWAP_CNTL, GRPH_ENDIAN_SWAP,
					ENDIAN_8IN16);
#endif
		break;
	case DRM_FORMAT_XRGB8888:
	case DRM_FORMAT_ARGB8888:
		fb_format = REG_SET_FIELD(0, GRPH_CONTROL, GRPH_DEPTH, 2);
		fb_format = REG_SET_FIELD(fb_format, GRPH_CONTROL, GRPH_FORMAT, 0);
#ifdef __BIG_ENDIAN
		fb_swap = REG_SET_FIELD(fb_swap, GRPH_SWAP_CNTL, GRPH_ENDIAN_SWAP,
					ENDIAN_8IN32);
#endif
		break;
	case DRM_FORMAT_XRGB2101010:
	case DRM_FORMAT_ARGB2101010:
		fb_format = REG_SET_FIELD(0, GRPH_CONTROL, GRPH_DEPTH, 2);
		fb_format = REG_SET_FIELD(fb_format, GRPH_CONTROL, GRPH_FORMAT, 1);
#ifdef __BIG_ENDIAN
		fb_swap = REG_SET_FIELD(fb_swap, GRPH_SWAP_CNTL, GRPH_ENDIAN_SWAP,
					ENDIAN_8IN32);
#endif
		/* Greater 8 bpc fb needs to bypass hw-lut to retain precision */
		bypass_lut = true;
		break;
	case DRM_FORMAT_BGRX1010102:
	case DRM_FORMAT_BGRA1010102:
		fb_format = REG_SET_FIELD(0, GRPH_CONTROL, GRPH_DEPTH, 2);
		fb_format = REG_SET_FIELD(fb_format, GRPH_CONTROL, GRPH_FORMAT, 4);
#ifdef __BIG_ENDIAN
		fb_swap = REG_SET_FIELD(fb_swap, GRPH_SWAP_CNTL, GRPH_ENDIAN_SWAP,
					ENDIAN_8IN32);
#endif
		/* Greater 8 bpc fb needs to bypass hw-lut to retain precision */
		bypass_lut = true;
		break;
	case DRM_FORMAT_XBGR8888:
	case DRM_FORMAT_ABGR8888:
		fb_format = REG_SET_FIELD(0, GRPH_CONTROL, GRPH_DEPTH, 2);
		fb_format = REG_SET_FIELD(fb_format, GRPH_CONTROL, GRPH_FORMAT, 0);
		fb_swap = REG_SET_FIELD(fb_swap, GRPH_SWAP_CNTL, GRPH_RED_CROSSBAR, 2);
		fb_swap = REG_SET_FIELD(fb_swap, GRPH_SWAP_CNTL, GRPH_BLUE_CROSSBAR, 2);
#ifdef __BIG_ENDIAN
		fb_swap = REG_SET_FIELD(fb_swap, GRPH_SWAP_CNTL, GRPH_ENDIAN_SWAP,
					ENDIAN_8IN32);
#endif
		break;
	default:
		DRM_ERROR("Unsupported screen format %s\n",
		          drm_get_format_name(target_fb->format->format, &format_name));
		return -EINVAL;
	}

	if (AMDGPU_TILING_GET(tiling_flags, ARRAY_MODE) == ARRAY_2D_TILED_THIN1) {
		unsigned bankw, bankh, mtaspect, tile_split, num_banks;

		bankw = AMDGPU_TILING_GET(tiling_flags, BANK_WIDTH);
		bankh = AMDGPU_TILING_GET(tiling_flags, BANK_HEIGHT);
		mtaspect = AMDGPU_TILING_GET(tiling_flags, MACRO_TILE_ASPECT);
		tile_split = AMDGPU_TILING_GET(tiling_flags, TILE_SPLIT);
		num_banks = AMDGPU_TILING_GET(tiling_flags, NUM_BANKS);

		fb_format = REG_SET_FIELD(fb_format, GRPH_CONTROL, GRPH_NUM_BANKS, num_banks);
		fb_format = REG_SET_FIELD(fb_format, GRPH_CONTROL, GRPH_ARRAY_MODE,
					  ARRAY_2D_TILED_THIN1);
		fb_format = REG_SET_FIELD(fb_format, GRPH_CONTROL, GRPH_TILE_SPLIT,
					  tile_split);
		fb_format = REG_SET_FIELD(fb_format, GRPH_CONTROL, GRPH_BANK_WIDTH, bankw);
		fb_format = REG_SET_FIELD(fb_format, GRPH_CONTROL, GRPH_BANK_HEIGHT, bankh);
		fb_format = REG_SET_FIELD(fb_format, GRPH_CONTROL, GRPH_MACRO_TILE_ASPECT,
					  mtaspect);
		fb_format = REG_SET_FIELD(fb_format, GRPH_CONTROL, GRPH_MICRO_TILE_MODE,
					  ADDR_SURF_MICRO_TILING_DISPLAY);
	} else if (AMDGPU_TILING_GET(tiling_flags, ARRAY_MODE) == ARRAY_1D_TILED_THIN1) {
		fb_format = REG_SET_FIELD(fb_format, GRPH_CONTROL, GRPH_ARRAY_MODE,
					  ARRAY_1D_TILED_THIN1);
	}

	fb_format = REG_SET_FIELD(fb_format, GRPH_CONTROL, GRPH_PIPE_CONFIG,
				  pipe_config);

	dce_v10_0_vga_enable(crtc, false);

	/* Make sure surface address is updated at vertical blank rather than
	 * horizontal blank
	 */
	tmp = RREG32(mmGRPH_FLIP_CONTROL + amdgpu_crtc->crtc_offset);
	tmp = REG_SET_FIELD(tmp, GRPH_FLIP_CONTROL,
			    GRPH_SURFACE_UPDATE_H_RETRACE_EN, 0);
	WREG32(mmGRPH_FLIP_CONTROL + amdgpu_crtc->crtc_offset, tmp);

	WREG32(mmGRPH_PRIMARY_SURFACE_ADDRESS_HIGH + amdgpu_crtc->crtc_offset,
	       upper_32_bits(fb_location));
	WREG32(mmGRPH_SECONDARY_SURFACE_ADDRESS_HIGH + amdgpu_crtc->crtc_offset,
	       upper_32_bits(fb_location));
	WREG32(mmGRPH_PRIMARY_SURFACE_ADDRESS + amdgpu_crtc->crtc_offset,
	       (u32)fb_location & GRPH_PRIMARY_SURFACE_ADDRESS__GRPH_PRIMARY_SURFACE_ADDRESS_MASK);
	WREG32(mmGRPH_SECONDARY_SURFACE_ADDRESS + amdgpu_crtc->crtc_offset,
	       (u32) fb_location & GRPH_SECONDARY_SURFACE_ADDRESS__GRPH_SECONDARY_SURFACE_ADDRESS_MASK);
	WREG32(mmGRPH_CONTROL + amdgpu_crtc->crtc_offset, fb_format);
	WREG32(mmGRPH_SWAP_CNTL + amdgpu_crtc->crtc_offset, fb_swap);

	/*
	 * The LUT only has 256 slots for indexing by a 8 bpc fb. Bypass the LUT
	 * for > 8 bpc scanout to avoid truncation of fb indices to 8 msb's, to
	 * retain the full precision throughout the pipeline.
	 */
	tmp = RREG32(mmGRPH_LUT_10BIT_BYPASS + amdgpu_crtc->crtc_offset);
	if (bypass_lut)
		tmp = REG_SET_FIELD(tmp, GRPH_LUT_10BIT_BYPASS, GRPH_LUT_10BIT_BYPASS_EN, 1);
	else
		tmp = REG_SET_FIELD(tmp, GRPH_LUT_10BIT_BYPASS, GRPH_LUT_10BIT_BYPASS_EN, 0);
	WREG32(mmGRPH_LUT_10BIT_BYPASS + amdgpu_crtc->crtc_offset, tmp);

	if (bypass_lut)
		DRM_DEBUG_KMS("Bypassing hardware LUT due to 10 bit fb scanout.\n");

	WREG32(mmGRPH_SURFACE_OFFSET_X + amdgpu_crtc->crtc_offset, 0);
	WREG32(mmGRPH_SURFACE_OFFSET_Y + amdgpu_crtc->crtc_offset, 0);
	WREG32(mmGRPH_X_START + amdgpu_crtc->crtc_offset, 0);
	WREG32(mmGRPH_Y_START + amdgpu_crtc->crtc_offset, 0);
	WREG32(mmGRPH_X_END + amdgpu_crtc->crtc_offset, target_fb->width);
	WREG32(mmGRPH_Y_END + amdgpu_crtc->crtc_offset, target_fb->height);

	fb_pitch_pixels = target_fb->pitches[0] / target_fb->format->cpp[0];
	WREG32(mmGRPH_PITCH + amdgpu_crtc->crtc_offset, fb_pitch_pixels);

	dce_v10_0_grph_enable(crtc, true);

	WREG32(mmLB_DESKTOP_HEIGHT + amdgpu_crtc->crtc_offset,
	       target_fb->height);

	x &= ~3;
	y &= ~1;
	WREG32(mmVIEWPORT_START + amdgpu_crtc->crtc_offset,
	       (x << 16) | y);
	viewport_w = crtc->mode.hdisplay;
	viewport_h = (crtc->mode.vdisplay + 1) & ~1;
	WREG32(mmVIEWPORT_SIZE + amdgpu_crtc->crtc_offset,
	       (viewport_w << 16) | viewport_h);

	/* set pageflip to happen anywhere in vblank interval */
	WREG32(mmMASTER_UPDATE_MODE + amdgpu_crtc->crtc_offset, 0);

	if (!atomic && fb && fb != crtc->primary->fb) {
		abo = gem_to_amdgpu_bo(fb->obj[0]);
		r = amdgpu_bo_reserve(abo, true);
		if (unlikely(r != 0))
			return r;
		amdgpu_bo_unpin(abo);
		amdgpu_bo_unreserve(abo);
	}

	/* Bytes per pixel may have changed */
	dce_v10_0_bandwidth_update(adev);

	return 0;
}