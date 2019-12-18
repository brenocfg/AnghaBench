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
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int u32 ;
struct TYPE_5__ {int vram_start; } ;
struct radeon_device {TYPE_2__ mc; } ;
struct radeon_crtc {int legacy_display_base_addr; int crtc_id; int crtc_offset; } ;
struct radeon_bo {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct drm_framebuffer {int* pitches; struct drm_gem_object** obj; TYPE_3__* format; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct drm_crtc {TYPE_1__* primary; struct drm_device* dev; } ;
struct TYPE_6__ {int* cpp; } ;
struct TYPE_4__ {struct drm_framebuffer* fb; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_R300 (struct radeon_device*) ; 
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int R300_CRTC2_TILE_X0_Y0 ; 
 int R300_CRTC_MACRO_TILE_EN ; 
 int R300_CRTC_MICRO_TILE_BUFFER_DIS ; 
 int R300_CRTC_TILE_X0_Y0 ; 
 int R300_CRTC_X_Y_MODE_EN ; 
 int RADEON_CRTC2_GEN_CNTL ; 
 int RADEON_CRTC_GEN_CNTL ; 
 int RADEON_CRTC_GUI_TRIG_OFFSET_LEFT_EN ; 
 int RADEON_CRTC_OFFSET ; 
 int RADEON_CRTC_OFFSET_CNTL ; 
 int RADEON_CRTC_PITCH ; 
 int RADEON_CRTC_TILE_EN ; 
 int RADEON_CRTC_VSTAT_MODE_MASK ; 
 int RADEON_DISPLAY_BASE_ADDR ; 
 int /*<<< orphan*/  RADEON_GEM_DOMAIN_VRAM ; 
 int RADEON_TILING_MACRO ; 
 int RADEON_TILING_MICRO ; 
 int RREG32 (int) ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 struct radeon_bo* gem_to_radeon_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  radeon_bandwidth_update (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_bo_get_tiling_flags (struct radeon_bo*,int*,int /*<<< orphan*/ *) ; 
 int radeon_bo_pin_restricted (struct radeon_bo*,int /*<<< orphan*/ ,int,int*) ; 
 int radeon_bo_reserve (struct radeon_bo*,int) ; 
 unsigned long radeon_bo_size (struct radeon_bo*) ; 
 int /*<<< orphan*/  radeon_bo_unpin (struct radeon_bo*) ; 
 int /*<<< orphan*/  radeon_bo_unreserve (struct radeon_bo*) ; 
 struct radeon_crtc* to_radeon_crtc (struct drm_crtc*) ; 
 scalar_t__ unlikely (int) ; 

int radeon_crtc_do_set_base(struct drm_crtc *crtc,
			 struct drm_framebuffer *fb,
			 int x, int y, int atomic)
{
	struct drm_device *dev = crtc->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	struct drm_framebuffer *target_fb;
	struct drm_gem_object *obj;
	struct radeon_bo *rbo;
	uint64_t base;
	uint32_t crtc_offset, crtc_offset_cntl, crtc_tile_x0_y0 = 0;
	uint32_t crtc_pitch, pitch_pixels;
	uint32_t tiling_flags;
	int format;
	uint32_t gen_cntl_reg, gen_cntl_val;
	int r;

	DRM_DEBUG_KMS("\n");
	/* no fb bound */
	if (!atomic && !crtc->primary->fb) {
		DRM_DEBUG_KMS("No FB bound\n");
		return 0;
	}

	if (atomic)
		target_fb = fb;
	else
		target_fb = crtc->primary->fb;

	switch (target_fb->format->cpp[0] * 8) {
	case 8:
		format = 2;
		break;
	case 15:      /*  555 */
		format = 3;
		break;
	case 16:      /*  565 */
		format = 4;
		break;
	case 24:      /*  RGB */
		format = 5;
		break;
	case 32:      /* xRGB */
		format = 6;
		break;
	default:
		return false;
	}

	/* Pin framebuffer & get tilling informations */
	obj = target_fb->obj[0];
	rbo = gem_to_radeon_bo(obj);
retry:
	r = radeon_bo_reserve(rbo, false);
	if (unlikely(r != 0))
		return r;
	/* Only 27 bit offset for legacy CRTC */
	r = radeon_bo_pin_restricted(rbo, RADEON_GEM_DOMAIN_VRAM, 1 << 27,
				     &base);
	if (unlikely(r != 0)) {
		radeon_bo_unreserve(rbo);

		/* On old GPU like RN50 with little vram pining can fails because
		 * current fb is taking all space needed. So instead of unpining
		 * the old buffer after pining the new one, first unpin old one
		 * and then retry pining new one.
		 *
		 * As only master can set mode only master can pin and it is
		 * unlikely the master client will race with itself especialy
		 * on those old gpu with single crtc.
		 *
		 * We don't shutdown the display controller because new buffer
		 * will end up in same spot.
		 */
		if (!atomic && fb && fb != crtc->primary->fb) {
			struct radeon_bo *old_rbo;
			unsigned long nsize, osize;

			old_rbo = gem_to_radeon_bo(fb->obj[0]);
			osize = radeon_bo_size(old_rbo);
			nsize = radeon_bo_size(rbo);
			if (nsize <= osize && !radeon_bo_reserve(old_rbo, false)) {
				radeon_bo_unpin(old_rbo);
				radeon_bo_unreserve(old_rbo);
				fb = NULL;
				goto retry;
			}
		}
		return -EINVAL;
	}
	radeon_bo_get_tiling_flags(rbo, &tiling_flags, NULL);
	radeon_bo_unreserve(rbo);
	if (tiling_flags & RADEON_TILING_MICRO)
		DRM_ERROR("trying to scanout microtiled buffer\n");

	/* if scanout was in GTT this really wouldn't work */
	/* crtc offset is from display base addr not FB location */
	radeon_crtc->legacy_display_base_addr = rdev->mc.vram_start;

	base -= radeon_crtc->legacy_display_base_addr;

	crtc_offset_cntl = 0;

	pitch_pixels = target_fb->pitches[0] / target_fb->format->cpp[0];
	crtc_pitch = DIV_ROUND_UP(pitch_pixels * target_fb->format->cpp[0] * 8,
				  target_fb->format->cpp[0] * 8 * 8);
	crtc_pitch |= crtc_pitch << 16;

	crtc_offset_cntl |= RADEON_CRTC_GUI_TRIG_OFFSET_LEFT_EN;
	if (tiling_flags & RADEON_TILING_MACRO) {
		if (ASIC_IS_R300(rdev))
			crtc_offset_cntl |= (R300_CRTC_X_Y_MODE_EN |
					     R300_CRTC_MICRO_TILE_BUFFER_DIS |
					     R300_CRTC_MACRO_TILE_EN);
		else
			crtc_offset_cntl |= RADEON_CRTC_TILE_EN;
	} else {
		if (ASIC_IS_R300(rdev))
			crtc_offset_cntl &= ~(R300_CRTC_X_Y_MODE_EN |
					      R300_CRTC_MICRO_TILE_BUFFER_DIS |
					      R300_CRTC_MACRO_TILE_EN);
		else
			crtc_offset_cntl &= ~RADEON_CRTC_TILE_EN;
	}

	if (tiling_flags & RADEON_TILING_MACRO) {
		if (ASIC_IS_R300(rdev)) {
			crtc_tile_x0_y0 = x | (y << 16);
			base &= ~0x7ff;
		} else {
			int byteshift = target_fb->format->cpp[0] * 8 >> 4;
			int tile_addr = (((y >> 3) * pitch_pixels +  x) >> (8 - byteshift)) << 11;
			base += tile_addr + ((x << byteshift) % 256) + ((y % 8) << 8);
			crtc_offset_cntl |= (y % 16);
		}
	} else {
		int offset = y * pitch_pixels + x;
		switch (target_fb->format->cpp[0] * 8) {
		case 8:
			offset *= 1;
			break;
		case 15:
		case 16:
			offset *= 2;
			break;
		case 24:
			offset *= 3;
			break;
		case 32:
			offset *= 4;
			break;
		default:
			return false;
		}
		base += offset;
	}

	base &= ~7;

	if (radeon_crtc->crtc_id == 1)
		gen_cntl_reg = RADEON_CRTC2_GEN_CNTL;
	else
		gen_cntl_reg = RADEON_CRTC_GEN_CNTL;

	gen_cntl_val = RREG32(gen_cntl_reg);
	gen_cntl_val &= ~(0xf << 8);
	gen_cntl_val |= (format << 8);
	gen_cntl_val &= ~RADEON_CRTC_VSTAT_MODE_MASK;
	WREG32(gen_cntl_reg, gen_cntl_val);

	crtc_offset = (u32)base;

	WREG32(RADEON_DISPLAY_BASE_ADDR + radeon_crtc->crtc_offset, radeon_crtc->legacy_display_base_addr);

	if (ASIC_IS_R300(rdev)) {
		if (radeon_crtc->crtc_id)
			WREG32(R300_CRTC2_TILE_X0_Y0, crtc_tile_x0_y0);
		else
			WREG32(R300_CRTC_TILE_X0_Y0, crtc_tile_x0_y0);
	}
	WREG32(RADEON_CRTC_OFFSET_CNTL + radeon_crtc->crtc_offset, crtc_offset_cntl);
	WREG32(RADEON_CRTC_OFFSET + radeon_crtc->crtc_offset, crtc_offset);
	WREG32(RADEON_CRTC_PITCH + radeon_crtc->crtc_offset, crtc_pitch);

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