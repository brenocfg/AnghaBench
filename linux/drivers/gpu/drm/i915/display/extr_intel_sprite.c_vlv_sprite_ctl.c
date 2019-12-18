#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {unsigned int rotation; scalar_t__ color_encoding; struct drm_framebuffer* fb; } ;
struct drm_intel_sprite_colorkey {int flags; } ;
struct intel_plane_state {TYPE_2__ base; struct drm_intel_sprite_colorkey ckey; } ;
struct intel_crtc_state {int dummy; } ;
struct drm_framebuffer {scalar_t__ modifier; TYPE_1__* format; } ;
struct TYPE_3__ {int format; } ;

/* Variables and functions */
 scalar_t__ DRM_COLOR_YCBCR_BT709 ; 
#define  DRM_FORMAT_ABGR2101010 138 
#define  DRM_FORMAT_ABGR8888 137 
#define  DRM_FORMAT_ARGB8888 136 
#define  DRM_FORMAT_RGB565 135 
#define  DRM_FORMAT_UYVY 134 
#define  DRM_FORMAT_VYUY 133 
#define  DRM_FORMAT_XBGR2101010 132 
#define  DRM_FORMAT_XBGR8888 131 
#define  DRM_FORMAT_XRGB8888 130 
#define  DRM_FORMAT_YUYV 129 
#define  DRM_FORMAT_YVYU 128 
 unsigned int DRM_MODE_REFLECT_X ; 
 unsigned int DRM_MODE_ROTATE_180 ; 
 scalar_t__ I915_FORMAT_MOD_X_TILED ; 
 int I915_SET_COLORKEY_SOURCE ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 int SP_ENABLE ; 
 int SP_FORMAT_BGR565 ; 
 int SP_FORMAT_BGRA8888 ; 
 int SP_FORMAT_BGRX8888 ; 
 int SP_FORMAT_RGBA1010102 ; 
 int SP_FORMAT_RGBA8888 ; 
 int SP_FORMAT_RGBX1010102 ; 
 int SP_FORMAT_RGBX8888 ; 
 int SP_FORMAT_YUV422 ; 
 int SP_MIRROR ; 
 int SP_ROTATE_180 ; 
 int SP_SOURCE_KEY ; 
 int SP_TILED ; 
 int SP_YUV_FORMAT_BT709 ; 
 int SP_YUV_ORDER_UYVY ; 
 int SP_YUV_ORDER_VYUY ; 
 int SP_YUV_ORDER_YUYV ; 
 int SP_YUV_ORDER_YVYU ; 

__attribute__((used)) static u32 vlv_sprite_ctl(const struct intel_crtc_state *crtc_state,
			  const struct intel_plane_state *plane_state)
{
	const struct drm_framebuffer *fb = plane_state->base.fb;
	unsigned int rotation = plane_state->base.rotation;
	const struct drm_intel_sprite_colorkey *key = &plane_state->ckey;
	u32 sprctl;

	sprctl = SP_ENABLE;

	switch (fb->format->format) {
	case DRM_FORMAT_YUYV:
		sprctl |= SP_FORMAT_YUV422 | SP_YUV_ORDER_YUYV;
		break;
	case DRM_FORMAT_YVYU:
		sprctl |= SP_FORMAT_YUV422 | SP_YUV_ORDER_YVYU;
		break;
	case DRM_FORMAT_UYVY:
		sprctl |= SP_FORMAT_YUV422 | SP_YUV_ORDER_UYVY;
		break;
	case DRM_FORMAT_VYUY:
		sprctl |= SP_FORMAT_YUV422 | SP_YUV_ORDER_VYUY;
		break;
	case DRM_FORMAT_RGB565:
		sprctl |= SP_FORMAT_BGR565;
		break;
	case DRM_FORMAT_XRGB8888:
		sprctl |= SP_FORMAT_BGRX8888;
		break;
	case DRM_FORMAT_ARGB8888:
		sprctl |= SP_FORMAT_BGRA8888;
		break;
	case DRM_FORMAT_XBGR2101010:
		sprctl |= SP_FORMAT_RGBX1010102;
		break;
	case DRM_FORMAT_ABGR2101010:
		sprctl |= SP_FORMAT_RGBA1010102;
		break;
	case DRM_FORMAT_XBGR8888:
		sprctl |= SP_FORMAT_RGBX8888;
		break;
	case DRM_FORMAT_ABGR8888:
		sprctl |= SP_FORMAT_RGBA8888;
		break;
	default:
		MISSING_CASE(fb->format->format);
		return 0;
	}

	if (plane_state->base.color_encoding == DRM_COLOR_YCBCR_BT709)
		sprctl |= SP_YUV_FORMAT_BT709;

	if (fb->modifier == I915_FORMAT_MOD_X_TILED)
		sprctl |= SP_TILED;

	if (rotation & DRM_MODE_ROTATE_180)
		sprctl |= SP_ROTATE_180;

	if (rotation & DRM_MODE_REFLECT_X)
		sprctl |= SP_MIRROR;

	if (key->flags & I915_SET_COLORKEY_SOURCE)
		sprctl |= SP_SOURCE_KEY;

	return sprctl;
}