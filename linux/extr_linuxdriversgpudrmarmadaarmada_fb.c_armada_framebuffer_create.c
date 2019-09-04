#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
struct drm_mode_fb_cmd2 {int pixel_format; } ;
struct drm_device {int dummy; } ;
struct armada_gem_object {int /*<<< orphan*/  obj; } ;
struct TYPE_3__ {int /*<<< orphan*/ ** obj; } ;
struct armada_framebuffer {TYPE_1__ fb; void* mod; void* fmt; } ;

/* Variables and functions */
 void* CFG_1555 ; 
 void* CFG_420 ; 
 void* CFG_422 ; 
 void* CFG_422PACK ; 
 void* CFG_565 ; 
 void* CFG_8888 ; 
 void* CFG_888PACK ; 
 void* CFG_PSEUDO8 ; 
 void* CFG_SWAPRB ; 
 int CFG_SWAPUV ; 
 int CFG_SWAPYU ; 
 void* CFG_X888 ; 
 int CFG_YUV2RGB ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
#define  DRM_FORMAT_ABGR1555 146 
#define  DRM_FORMAT_ABGR8888 145 
#define  DRM_FORMAT_ARGB1555 144 
#define  DRM_FORMAT_ARGB8888 143 
#define  DRM_FORMAT_BGR565 142 
#define  DRM_FORMAT_BGR888 141 
#define  DRM_FORMAT_C8 140 
#define  DRM_FORMAT_RGB565 139 
#define  DRM_FORMAT_RGB888 138 
#define  DRM_FORMAT_UYVY 137 
#define  DRM_FORMAT_VYUY 136 
#define  DRM_FORMAT_XBGR8888 135 
#define  DRM_FORMAT_XRGB8888 134 
#define  DRM_FORMAT_YUV420 133 
#define  DRM_FORMAT_YUV422 132 
#define  DRM_FORMAT_YUYV 131 
#define  DRM_FORMAT_YVU420 130 
#define  DRM_FORMAT_YVU422 129 
#define  DRM_FORMAT_YVYU 128 
 int EINVAL ; 
 int ENOMEM ; 
 struct armada_framebuffer* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  armada_fb_funcs ; 
 int drm_framebuffer_init (struct drm_device*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_object_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_helper_mode_fill_fb_struct (struct drm_device*,TYPE_1__*,struct drm_mode_fb_cmd2 const*) ; 
 int /*<<< orphan*/  kfree (struct armada_framebuffer*) ; 
 struct armada_framebuffer* kzalloc (int,int /*<<< orphan*/ ) ; 

struct armada_framebuffer *armada_framebuffer_create(struct drm_device *dev,
	const struct drm_mode_fb_cmd2 *mode, struct armada_gem_object *obj)
{
	struct armada_framebuffer *dfb;
	uint8_t format, config;
	int ret;

	switch (mode->pixel_format) {
#define FMT(drm, fmt, mod)		\
	case DRM_FORMAT_##drm:		\
		format = CFG_##fmt;	\
		config = mod;		\
		break
	FMT(RGB565,	565,		CFG_SWAPRB);
	FMT(BGR565,	565,		0);
	FMT(ARGB1555,	1555,		CFG_SWAPRB);
	FMT(ABGR1555,	1555,		0);
	FMT(RGB888,	888PACK,	CFG_SWAPRB);
	FMT(BGR888,	888PACK,	0);
	FMT(XRGB8888,	X888,		CFG_SWAPRB);
	FMT(XBGR8888,	X888,		0);
	FMT(ARGB8888,	8888,		CFG_SWAPRB);
	FMT(ABGR8888,	8888,		0);
	FMT(YUYV,	422PACK,	CFG_YUV2RGB | CFG_SWAPYU | CFG_SWAPUV);
	FMT(UYVY,	422PACK,	CFG_YUV2RGB);
	FMT(VYUY,	422PACK,	CFG_YUV2RGB | CFG_SWAPUV);
	FMT(YVYU,	422PACK,	CFG_YUV2RGB | CFG_SWAPYU);
	FMT(YUV422,	422,		CFG_YUV2RGB);
	FMT(YVU422,	422,		CFG_YUV2RGB | CFG_SWAPUV);
	FMT(YUV420,	420,		CFG_YUV2RGB);
	FMT(YVU420,	420,		CFG_YUV2RGB | CFG_SWAPUV);
	FMT(C8,		PSEUDO8,	0);
#undef FMT
	default:
		return ERR_PTR(-EINVAL);
	}

	dfb = kzalloc(sizeof(*dfb), GFP_KERNEL);
	if (!dfb) {
		DRM_ERROR("failed to allocate Armada fb object\n");
		return ERR_PTR(-ENOMEM);
	}

	dfb->fmt = format;
	dfb->mod = config;
	dfb->fb.obj[0] = &obj->obj;

	drm_helper_mode_fill_fb_struct(dev, &dfb->fb, mode);

	ret = drm_framebuffer_init(dev, &dfb->fb, &armada_fb_funcs);
	if (ret) {
		kfree(dfb);
		return ERR_PTR(ret);
	}

	/*
	 * Take a reference on our object as we're successful - the
	 * caller already holds a reference, which keeps us safe for
	 * the above call, but the caller will drop their reference
	 * to it.  Hence we need to take our own reference.
	 */
	drm_gem_object_get(&obj->obj);

	return dfb;
}