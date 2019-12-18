#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
typedef  int u32 ;
struct TYPE_12__ {int* macrotile_mode_array; int* tile_mode_array; } ;
struct TYPE_11__ {int tile_config; } ;
struct TYPE_10__ {int tile_config; } ;
struct TYPE_9__ {int* tile_mode_array; } ;
struct TYPE_13__ {TYPE_4__ cik; TYPE_3__ evergreen; TYPE_2__ cayman; TYPE_1__ si; } ;
struct radeon_device {scalar_t__ family; TYPE_5__ config; } ;
struct radeon_crtc {int crtc_id; scalar_t__ crtc_offset; } ;
struct radeon_bo {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct drm_framebuffer {int width; int height; int* pitches; struct drm_gem_object** obj; TYPE_6__* format; } ;
struct drm_format_name_buf {int dummy; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct TYPE_15__ {int hdisplay; int vdisplay; int flags; } ;
struct drm_crtc {TYPE_8__* primary; TYPE_7__ mode; struct drm_device* dev; } ;
struct TYPE_16__ {struct drm_framebuffer* fb; } ;
struct TYPE_14__ {int format; int* cpp; } ;

/* Variables and functions */
 scalar_t__ AVIVO_D1VGA_CONTROL ; 
 scalar_t__ AVIVO_D2VGA_CONTROL ; 
 scalar_t__ CHIP_BONAIRE ; 
 scalar_t__ CHIP_CAYMAN ; 
 scalar_t__ CHIP_HAINAN ; 
 scalar_t__ CHIP_OLAND ; 
 scalar_t__ CHIP_PITCAIRN ; 
 scalar_t__ CHIP_TAHITI ; 
 scalar_t__ CHIP_VERDE ; 
 int /*<<< orphan*/  CIK_DISPLAY_MICRO_TILING ; 
 int CIK_GRPH_MICRO_TILE_MODE (int /*<<< orphan*/ ) ; 
 int CIK_GRPH_PIPE_CONFIG (int) ; 
 scalar_t__ CIK_LB_DESKTOP_HEIGHT ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,...) ; 
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
 int DRM_MODE_FLAG_INTERLACE ; 
 int EINVAL ; 
 unsigned int EVERGREEN_ADDR_SURF_16_BANK ; 
 unsigned int EVERGREEN_ADDR_SURF_4_BANK ; 
 unsigned int EVERGREEN_ADDR_SURF_8_BANK ; 
 scalar_t__ EVERGREEN_D3VGA_CONTROL ; 
 scalar_t__ EVERGREEN_D4VGA_CONTROL ; 
 scalar_t__ EVERGREEN_D5VGA_CONTROL ; 
 scalar_t__ EVERGREEN_D6VGA_CONTROL ; 
 scalar_t__ EVERGREEN_DESKTOP_HEIGHT ; 
 int /*<<< orphan*/  EVERGREEN_GRPH_ARRAY_1D_TILED_THIN1 ; 
 int /*<<< orphan*/  EVERGREEN_GRPH_ARRAY_2D_TILED_THIN1 ; 
 int EVERGREEN_GRPH_ARRAY_MODE (int /*<<< orphan*/ ) ; 
 int EVERGREEN_GRPH_BANK_HEIGHT (unsigned int) ; 
 int EVERGREEN_GRPH_BANK_WIDTH (unsigned int) ; 
 int EVERGREEN_GRPH_BLUE_CROSSBAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVERGREEN_GRPH_BLUE_SEL_R ; 
 scalar_t__ EVERGREEN_GRPH_CONTROL ; 
 int EVERGREEN_GRPH_DEPTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVERGREEN_GRPH_DEPTH_16BPP ; 
 int /*<<< orphan*/  EVERGREEN_GRPH_DEPTH_32BPP ; 
 int /*<<< orphan*/  EVERGREEN_GRPH_DEPTH_8BPP ; 
 scalar_t__ EVERGREEN_GRPH_ENABLE ; 
 int /*<<< orphan*/  EVERGREEN_GRPH_ENDIAN_8IN16 ; 
 int /*<<< orphan*/  EVERGREEN_GRPH_ENDIAN_8IN32 ; 
 int /*<<< orphan*/  EVERGREEN_GRPH_ENDIAN_NONE ; 
 int EVERGREEN_GRPH_ENDIAN_SWAP (int /*<<< orphan*/ ) ; 
 scalar_t__ EVERGREEN_GRPH_FLIP_CONTROL ; 
 int EVERGREEN_GRPH_FORMAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVERGREEN_GRPH_FORMAT_ARGB1555 ; 
 int /*<<< orphan*/  EVERGREEN_GRPH_FORMAT_ARGB2101010 ; 
 int /*<<< orphan*/  EVERGREEN_GRPH_FORMAT_ARGB4444 ; 
 int /*<<< orphan*/  EVERGREEN_GRPH_FORMAT_ARGB565 ; 
 int /*<<< orphan*/  EVERGREEN_GRPH_FORMAT_ARGB8888 ; 
 int /*<<< orphan*/  EVERGREEN_GRPH_FORMAT_BGRA1010102 ; 
 int /*<<< orphan*/  EVERGREEN_GRPH_FORMAT_BGRA5551 ; 
 int /*<<< orphan*/  EVERGREEN_GRPH_FORMAT_INDEXED ; 
 scalar_t__ EVERGREEN_GRPH_LUT_10BIT_BYPASS_CONTROL ; 
 int EVERGREEN_GRPH_MACRO_TILE_ASPECT (unsigned int) ; 
 int EVERGREEN_GRPH_NUM_BANKS (unsigned int) ; 
 scalar_t__ EVERGREEN_GRPH_PITCH ; 
 scalar_t__ EVERGREEN_GRPH_PRIMARY_SURFACE_ADDRESS ; 
 scalar_t__ EVERGREEN_GRPH_PRIMARY_SURFACE_ADDRESS_HIGH ; 
 int EVERGREEN_GRPH_RED_CROSSBAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVERGREEN_GRPH_RED_SEL_B ; 
 scalar_t__ EVERGREEN_GRPH_SECONDARY_SURFACE_ADDRESS ; 
 scalar_t__ EVERGREEN_GRPH_SECONDARY_SURFACE_ADDRESS_HIGH ; 
 int EVERGREEN_GRPH_SURFACE_ADDRESS_MASK ; 
 scalar_t__ EVERGREEN_GRPH_SURFACE_OFFSET_X ; 
 scalar_t__ EVERGREEN_GRPH_SURFACE_OFFSET_Y ; 
 scalar_t__ EVERGREEN_GRPH_SWAP_CONTROL ; 
 int EVERGREEN_GRPH_TILE_SPLIT (unsigned int) ; 
 scalar_t__ EVERGREEN_GRPH_X_END ; 
 scalar_t__ EVERGREEN_GRPH_X_START ; 
 scalar_t__ EVERGREEN_GRPH_Y_END ; 
 scalar_t__ EVERGREEN_GRPH_Y_START ; 
 int /*<<< orphan*/  EVERGREEN_LUT_10BIT_BYPASS_EN ; 
 scalar_t__ EVERGREEN_MASTER_UPDATE_MODE ; 
 scalar_t__ EVERGREEN_VIEWPORT_SIZE ; 
 scalar_t__ EVERGREEN_VIEWPORT_START ; 
 int /*<<< orphan*/  RADEON_GEM_DOMAIN_VRAM ; 
 int RADEON_TILING_MACRO ; 
 int RADEON_TILING_MICRO ; 
 int /*<<< orphan*/  SI_ADDR_SURF_P4_8x16 ; 
 int /*<<< orphan*/  SI_ADDR_SURF_P8_32x32_8x16 ; 
 int SI_GRPH_PIPE_CONFIG (int /*<<< orphan*/ ) ; 
 unsigned int SI_TILE_MODE_COLOR_2D_SCANOUT_16BPP ; 
 unsigned int SI_TILE_MODE_COLOR_2D_SCANOUT_32BPP ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 
 int /*<<< orphan*/  WREG32_P (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_get_format_name (int,struct drm_format_name_buf*) ; 
 int /*<<< orphan*/  evergreen_tiling_fields (int,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 
 struct radeon_bo* gem_to_radeon_bo (struct drm_gem_object*) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  radeon_bandwidth_update (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_bo_get_tiling_flags (struct radeon_bo*,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ radeon_bo_gpu_offset (struct radeon_bo*) ; 
 int radeon_bo_pin (struct radeon_bo*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int radeon_bo_reserve (struct radeon_bo*,int) ; 
 int /*<<< orphan*/  radeon_bo_unpin (struct radeon_bo*) ; 
 int /*<<< orphan*/  radeon_bo_unreserve (struct radeon_bo*) ; 
 struct radeon_crtc* to_radeon_crtc (struct drm_crtc*) ; 
 scalar_t__ unlikely (int) ; 
 int upper_32_bits (scalar_t__) ; 

__attribute__((used)) static int dce4_crtc_do_set_base(struct drm_crtc *crtc,
				 struct drm_framebuffer *fb,
				 int x, int y, int atomic)
{
	struct radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	struct drm_device *dev = crtc->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct drm_framebuffer *target_fb;
	struct drm_gem_object *obj;
	struct radeon_bo *rbo;
	uint64_t fb_location;
	uint32_t fb_format, fb_pitch_pixels, tiling_flags;
	unsigned bankw, bankh, mtaspect, tile_split;
	u32 fb_swap = EVERGREEN_GRPH_ENDIAN_SWAP(EVERGREEN_GRPH_ENDIAN_NONE);
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
	rbo = gem_to_radeon_bo(obj);
	r = radeon_bo_reserve(rbo, false);
	if (unlikely(r != 0))
		return r;

	if (atomic)
		fb_location = radeon_bo_gpu_offset(rbo);
	else {
		r = radeon_bo_pin(rbo, RADEON_GEM_DOMAIN_VRAM, &fb_location);
		if (unlikely(r != 0)) {
			radeon_bo_unreserve(rbo);
			return -EINVAL;
		}
	}

	radeon_bo_get_tiling_flags(rbo, &tiling_flags, NULL);
	radeon_bo_unreserve(rbo);

	switch (target_fb->format->format) {
	case DRM_FORMAT_C8:
		fb_format = (EVERGREEN_GRPH_DEPTH(EVERGREEN_GRPH_DEPTH_8BPP) |
			     EVERGREEN_GRPH_FORMAT(EVERGREEN_GRPH_FORMAT_INDEXED));
		break;
	case DRM_FORMAT_XRGB4444:
	case DRM_FORMAT_ARGB4444:
		fb_format = (EVERGREEN_GRPH_DEPTH(EVERGREEN_GRPH_DEPTH_16BPP) |
			     EVERGREEN_GRPH_FORMAT(EVERGREEN_GRPH_FORMAT_ARGB4444));
#ifdef __BIG_ENDIAN
		fb_swap = EVERGREEN_GRPH_ENDIAN_SWAP(EVERGREEN_GRPH_ENDIAN_8IN16);
#endif
		break;
	case DRM_FORMAT_XRGB1555:
	case DRM_FORMAT_ARGB1555:
		fb_format = (EVERGREEN_GRPH_DEPTH(EVERGREEN_GRPH_DEPTH_16BPP) |
			     EVERGREEN_GRPH_FORMAT(EVERGREEN_GRPH_FORMAT_ARGB1555));
#ifdef __BIG_ENDIAN
		fb_swap = EVERGREEN_GRPH_ENDIAN_SWAP(EVERGREEN_GRPH_ENDIAN_8IN16);
#endif
		break;
	case DRM_FORMAT_BGRX5551:
	case DRM_FORMAT_BGRA5551:
		fb_format = (EVERGREEN_GRPH_DEPTH(EVERGREEN_GRPH_DEPTH_16BPP) |
			     EVERGREEN_GRPH_FORMAT(EVERGREEN_GRPH_FORMAT_BGRA5551));
#ifdef __BIG_ENDIAN
		fb_swap = EVERGREEN_GRPH_ENDIAN_SWAP(EVERGREEN_GRPH_ENDIAN_8IN16);
#endif
		break;
	case DRM_FORMAT_RGB565:
		fb_format = (EVERGREEN_GRPH_DEPTH(EVERGREEN_GRPH_DEPTH_16BPP) |
			     EVERGREEN_GRPH_FORMAT(EVERGREEN_GRPH_FORMAT_ARGB565));
#ifdef __BIG_ENDIAN
		fb_swap = EVERGREEN_GRPH_ENDIAN_SWAP(EVERGREEN_GRPH_ENDIAN_8IN16);
#endif
		break;
	case DRM_FORMAT_XRGB8888:
	case DRM_FORMAT_ARGB8888:
		fb_format = (EVERGREEN_GRPH_DEPTH(EVERGREEN_GRPH_DEPTH_32BPP) |
			     EVERGREEN_GRPH_FORMAT(EVERGREEN_GRPH_FORMAT_ARGB8888));
#ifdef __BIG_ENDIAN
		fb_swap = EVERGREEN_GRPH_ENDIAN_SWAP(EVERGREEN_GRPH_ENDIAN_8IN32);
#endif
		break;
	case DRM_FORMAT_XRGB2101010:
	case DRM_FORMAT_ARGB2101010:
		fb_format = (EVERGREEN_GRPH_DEPTH(EVERGREEN_GRPH_DEPTH_32BPP) |
			     EVERGREEN_GRPH_FORMAT(EVERGREEN_GRPH_FORMAT_ARGB2101010));
#ifdef __BIG_ENDIAN
		fb_swap = EVERGREEN_GRPH_ENDIAN_SWAP(EVERGREEN_GRPH_ENDIAN_8IN32);
#endif
		/* Greater 8 bpc fb needs to bypass hw-lut to retain precision */
		bypass_lut = true;
		break;
	case DRM_FORMAT_BGRX1010102:
	case DRM_FORMAT_BGRA1010102:
		fb_format = (EVERGREEN_GRPH_DEPTH(EVERGREEN_GRPH_DEPTH_32BPP) |
			     EVERGREEN_GRPH_FORMAT(EVERGREEN_GRPH_FORMAT_BGRA1010102));
#ifdef __BIG_ENDIAN
		fb_swap = EVERGREEN_GRPH_ENDIAN_SWAP(EVERGREEN_GRPH_ENDIAN_8IN32);
#endif
		/* Greater 8 bpc fb needs to bypass hw-lut to retain precision */
		bypass_lut = true;
		break;
	case DRM_FORMAT_XBGR8888:
	case DRM_FORMAT_ABGR8888:
		fb_format = (EVERGREEN_GRPH_DEPTH(EVERGREEN_GRPH_DEPTH_32BPP) |
			     EVERGREEN_GRPH_FORMAT(EVERGREEN_GRPH_FORMAT_ARGB8888));
		fb_swap = (EVERGREEN_GRPH_RED_CROSSBAR(EVERGREEN_GRPH_RED_SEL_B) |
			   EVERGREEN_GRPH_BLUE_CROSSBAR(EVERGREEN_GRPH_BLUE_SEL_R));
#ifdef __BIG_ENDIAN
		fb_swap |= EVERGREEN_GRPH_ENDIAN_SWAP(EVERGREEN_GRPH_ENDIAN_8IN32);
#endif
		break;
	default:
		DRM_ERROR("Unsupported screen format %s\n",
		          drm_get_format_name(target_fb->format->format, &format_name));
		return -EINVAL;
	}

	if (tiling_flags & RADEON_TILING_MACRO) {
		evergreen_tiling_fields(tiling_flags, &bankw, &bankh, &mtaspect, &tile_split);

		/* Set NUM_BANKS. */
		if (rdev->family >= CHIP_TAHITI) {
			unsigned index, num_banks;

			if (rdev->family >= CHIP_BONAIRE) {
				unsigned tileb, tile_split_bytes;

				/* Calculate the macrotile mode index. */
				tile_split_bytes = 64 << tile_split;
				tileb = 8 * 8 * target_fb->format->cpp[0];
				tileb = min(tile_split_bytes, tileb);

				for (index = 0; tileb > 64; index++)
					tileb >>= 1;

				if (index >= 16) {
					DRM_ERROR("Wrong screen bpp (%u) or tile split (%u)\n",
						  target_fb->format->cpp[0] * 8,
						  tile_split);
					return -EINVAL;
				}

				num_banks = (rdev->config.cik.macrotile_mode_array[index] >> 6) & 0x3;
			} else {
				switch (target_fb->format->cpp[0] * 8) {
				case 8:
					index = 10;
					break;
				case 16:
					index = SI_TILE_MODE_COLOR_2D_SCANOUT_16BPP;
					break;
				default:
				case 32:
					index = SI_TILE_MODE_COLOR_2D_SCANOUT_32BPP;
					break;
				}

				num_banks = (rdev->config.si.tile_mode_array[index] >> 20) & 0x3;
			}

			fb_format |= EVERGREEN_GRPH_NUM_BANKS(num_banks);
		} else {
			/* NI and older. */
			if (rdev->family >= CHIP_CAYMAN)
				tmp = rdev->config.cayman.tile_config;
			else
				tmp = rdev->config.evergreen.tile_config;

			switch ((tmp & 0xf0) >> 4) {
			case 0: /* 4 banks */
				fb_format |= EVERGREEN_GRPH_NUM_BANKS(EVERGREEN_ADDR_SURF_4_BANK);
				break;
			case 1: /* 8 banks */
			default:
				fb_format |= EVERGREEN_GRPH_NUM_BANKS(EVERGREEN_ADDR_SURF_8_BANK);
				break;
			case 2: /* 16 banks */
				fb_format |= EVERGREEN_GRPH_NUM_BANKS(EVERGREEN_ADDR_SURF_16_BANK);
				break;
			}
		}

		fb_format |= EVERGREEN_GRPH_ARRAY_MODE(EVERGREEN_GRPH_ARRAY_2D_TILED_THIN1);
		fb_format |= EVERGREEN_GRPH_TILE_SPLIT(tile_split);
		fb_format |= EVERGREEN_GRPH_BANK_WIDTH(bankw);
		fb_format |= EVERGREEN_GRPH_BANK_HEIGHT(bankh);
		fb_format |= EVERGREEN_GRPH_MACRO_TILE_ASPECT(mtaspect);
		if (rdev->family >= CHIP_BONAIRE) {
			/* XXX need to know more about the surface tiling mode */
			fb_format |= CIK_GRPH_MICRO_TILE_MODE(CIK_DISPLAY_MICRO_TILING);
		}
	} else if (tiling_flags & RADEON_TILING_MICRO)
		fb_format |= EVERGREEN_GRPH_ARRAY_MODE(EVERGREEN_GRPH_ARRAY_1D_TILED_THIN1);

	if (rdev->family >= CHIP_BONAIRE) {
		/* Read the pipe config from the 2D TILED SCANOUT mode.
		 * It should be the same for the other modes too, but not all
		 * modes set the pipe config field. */
		u32 pipe_config = (rdev->config.cik.tile_mode_array[10] >> 6) & 0x1f;

		fb_format |= CIK_GRPH_PIPE_CONFIG(pipe_config);
	} else if ((rdev->family == CHIP_TAHITI) ||
		   (rdev->family == CHIP_PITCAIRN))
		fb_format |= SI_GRPH_PIPE_CONFIG(SI_ADDR_SURF_P8_32x32_8x16);
	else if ((rdev->family == CHIP_VERDE) ||
		 (rdev->family == CHIP_OLAND) ||
		 (rdev->family == CHIP_HAINAN)) /* for completeness.  HAINAN has no display hw */
		fb_format |= SI_GRPH_PIPE_CONFIG(SI_ADDR_SURF_P4_8x16);

	switch (radeon_crtc->crtc_id) {
	case 0:
		WREG32(AVIVO_D1VGA_CONTROL, 0);
		break;
	case 1:
		WREG32(AVIVO_D2VGA_CONTROL, 0);
		break;
	case 2:
		WREG32(EVERGREEN_D3VGA_CONTROL, 0);
		break;
	case 3:
		WREG32(EVERGREEN_D4VGA_CONTROL, 0);
		break;
	case 4:
		WREG32(EVERGREEN_D5VGA_CONTROL, 0);
		break;
	case 5:
		WREG32(EVERGREEN_D6VGA_CONTROL, 0);
		break;
	default:
		break;
	}

	/* Make sure surface address is updated at vertical blank rather than
	 * horizontal blank
	 */
	WREG32(EVERGREEN_GRPH_FLIP_CONTROL + radeon_crtc->crtc_offset, 0);

	WREG32(EVERGREEN_GRPH_PRIMARY_SURFACE_ADDRESS_HIGH + radeon_crtc->crtc_offset,
	       upper_32_bits(fb_location));
	WREG32(EVERGREEN_GRPH_SECONDARY_SURFACE_ADDRESS_HIGH + radeon_crtc->crtc_offset,
	       upper_32_bits(fb_location));
	WREG32(EVERGREEN_GRPH_PRIMARY_SURFACE_ADDRESS + radeon_crtc->crtc_offset,
	       (u32)fb_location & EVERGREEN_GRPH_SURFACE_ADDRESS_MASK);
	WREG32(EVERGREEN_GRPH_SECONDARY_SURFACE_ADDRESS + radeon_crtc->crtc_offset,
	       (u32) fb_location & EVERGREEN_GRPH_SURFACE_ADDRESS_MASK);
	WREG32(EVERGREEN_GRPH_CONTROL + radeon_crtc->crtc_offset, fb_format);
	WREG32(EVERGREEN_GRPH_SWAP_CONTROL + radeon_crtc->crtc_offset, fb_swap);

	/*
	 * The LUT only has 256 slots for indexing by a 8 bpc fb. Bypass the LUT
	 * for > 8 bpc scanout to avoid truncation of fb indices to 8 msb's, to
	 * retain the full precision throughout the pipeline.
	 */
	WREG32_P(EVERGREEN_GRPH_LUT_10BIT_BYPASS_CONTROL + radeon_crtc->crtc_offset,
		 (bypass_lut ? EVERGREEN_LUT_10BIT_BYPASS_EN : 0),
		 ~EVERGREEN_LUT_10BIT_BYPASS_EN);

	if (bypass_lut)
		DRM_DEBUG_KMS("Bypassing hardware LUT due to 10 bit fb scanout.\n");

	WREG32(EVERGREEN_GRPH_SURFACE_OFFSET_X + radeon_crtc->crtc_offset, 0);
	WREG32(EVERGREEN_GRPH_SURFACE_OFFSET_Y + radeon_crtc->crtc_offset, 0);
	WREG32(EVERGREEN_GRPH_X_START + radeon_crtc->crtc_offset, 0);
	WREG32(EVERGREEN_GRPH_Y_START + radeon_crtc->crtc_offset, 0);
	WREG32(EVERGREEN_GRPH_X_END + radeon_crtc->crtc_offset, target_fb->width);
	WREG32(EVERGREEN_GRPH_Y_END + radeon_crtc->crtc_offset, target_fb->height);

	fb_pitch_pixels = target_fb->pitches[0] / target_fb->format->cpp[0];
	WREG32(EVERGREEN_GRPH_PITCH + radeon_crtc->crtc_offset, fb_pitch_pixels);
	WREG32(EVERGREEN_GRPH_ENABLE + radeon_crtc->crtc_offset, 1);

	if (rdev->family >= CHIP_BONAIRE)
		WREG32(CIK_LB_DESKTOP_HEIGHT + radeon_crtc->crtc_offset,
		       target_fb->height);
	else
		WREG32(EVERGREEN_DESKTOP_HEIGHT + radeon_crtc->crtc_offset,
		       target_fb->height);
	x &= ~3;
	y &= ~1;
	WREG32(EVERGREEN_VIEWPORT_START + radeon_crtc->crtc_offset,
	       (x << 16) | y);
	viewport_w = crtc->mode.hdisplay;
	viewport_h = (crtc->mode.vdisplay + 1) & ~1;
	if ((rdev->family >= CHIP_BONAIRE) &&
	    (crtc->mode.flags & DRM_MODE_FLAG_INTERLACE))
		viewport_h *= 2;
	WREG32(EVERGREEN_VIEWPORT_SIZE + radeon_crtc->crtc_offset,
	       (viewport_w << 16) | viewport_h);

	/* set pageflip to happen anywhere in vblank interval */
	WREG32(EVERGREEN_MASTER_UPDATE_MODE + radeon_crtc->crtc_offset, 0);

	if (!atomic && fb && fb != crtc->primary->fb) {
		rbo = gem_to_radeon_bo(fb->obj[0]);
		r = radeon_bo_reserve(rbo, false);
		if (unlikely(r != 0))
			return r;
		radeon_bo_unpin(rbo);
		radeon_bo_unreserve(rbo);
	}

	/* Bytes per pixel may have changed */
	radeon_bandwidth_update(rdev);

	return 0;
}