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
typedef  size_t u32 ;
struct platform_device {int dummy; } ;
struct TYPE_4__ {void* hw_ctx; int /*<<< orphan*/  base; } ;
struct kirin_drm_private {TYPE_2__ crtc; TYPE_1__* planes; void* hw_ctx; } ;
struct kirin_drm_data {size_t num_planes; size_t prim_plane; void* (* alloc_hw_ctx ) (struct platform_device*,int /*<<< orphan*/ *) ;} ;
struct drm_plane {int dummy; } ;
struct drm_device {struct kirin_drm_private* dev_private; int /*<<< orphan*/  dev; } ;
typedef  enum drm_plane_type { ____Placeholder_drm_plane_type } drm_plane_type ;
struct TYPE_3__ {size_t ch; struct drm_plane base; void* hw_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int DRM_PLANE_TYPE_OVERLAY ; 
 int DRM_PLANE_TYPE_PRIMARY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 struct kirin_drm_private* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int kirin_drm_crtc_init (struct drm_device*,int /*<<< orphan*/ *,struct drm_plane*,struct kirin_drm_data const*) ; 
 int kirin_drm_plane_init (struct drm_device*,struct drm_plane*,int,struct kirin_drm_data const*) ; 
 void* stub1 (struct platform_device*,int /*<<< orphan*/ *) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kirin_drm_private_init(struct drm_device *dev,
				  const struct kirin_drm_data *driver_data)
{
	struct platform_device *pdev = to_platform_device(dev->dev);
	struct kirin_drm_private *kirin_priv;
	struct drm_plane *prim_plane;
	enum drm_plane_type type;
	void *ctx;
	int ret;
	u32 ch;

	kirin_priv = devm_kzalloc(dev->dev, sizeof(*kirin_priv), GFP_KERNEL);
	if (!kirin_priv) {
		DRM_ERROR("failed to alloc kirin_drm_private\n");
		return -ENOMEM;
	}

	ctx = driver_data->alloc_hw_ctx(pdev, &kirin_priv->crtc.base);
	if (IS_ERR(ctx)) {
		DRM_ERROR("failed to initialize kirin_priv hw ctx\n");
		return -EINVAL;
	}
	kirin_priv->hw_ctx = ctx;

	/*
	 * plane init
	 * TODO: Now only support primary plane, overlay planes
	 * need to do.
	 */
	for (ch = 0; ch < driver_data->num_planes; ch++) {
		if (ch == driver_data->prim_plane)
			type = DRM_PLANE_TYPE_PRIMARY;
		else
			type = DRM_PLANE_TYPE_OVERLAY;
		ret = kirin_drm_plane_init(dev, &kirin_priv->planes[ch].base,
					   type, driver_data);
		if (ret)
			return ret;
		kirin_priv->planes[ch].ch = ch;
		kirin_priv->planes[ch].hw_ctx = ctx;
	}

	/* crtc init */
	prim_plane = &kirin_priv->planes[driver_data->prim_plane].base;
	ret = kirin_drm_crtc_init(dev, &kirin_priv->crtc.base,
				  prim_plane, driver_data);
	if (ret)
		return ret;
	kirin_priv->crtc.hw_ctx = ctx;
	dev->dev_private = kirin_priv;

	return 0;
}