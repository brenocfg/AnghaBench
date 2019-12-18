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
struct vmw_private {int capabilities; TYPE_1__* ldu_priv; int /*<<< orphan*/  active_display_unit; struct drm_device* dev; } ;
struct drm_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * fb; scalar_t__ last_num_active; scalar_t__ num_active; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int SVGA_CAP_MULTIMON ; 
 int VMWGFX_NUM_DISPLAY_UNITS ; 
 int drm_vblank_init (struct drm_device*,int) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_du_legacy ; 
 int /*<<< orphan*/  vmw_kms_create_implicit_placement_property (struct vmw_private*) ; 
 int /*<<< orphan*/  vmw_ldu_init (struct vmw_private*,int) ; 

int vmw_kms_ldu_init_display(struct vmw_private *dev_priv)
{
	struct drm_device *dev = dev_priv->dev;
	int i, ret;

	if (dev_priv->ldu_priv) {
		DRM_INFO("ldu system already on\n");
		return -EINVAL;
	}

	dev_priv->ldu_priv = kmalloc(sizeof(*dev_priv->ldu_priv), GFP_KERNEL);
	if (!dev_priv->ldu_priv)
		return -ENOMEM;

	INIT_LIST_HEAD(&dev_priv->ldu_priv->active);
	dev_priv->ldu_priv->num_active = 0;
	dev_priv->ldu_priv->last_num_active = 0;
	dev_priv->ldu_priv->fb = NULL;

	/* for old hardware without multimon only enable one display */
	if (dev_priv->capabilities & SVGA_CAP_MULTIMON)
		ret = drm_vblank_init(dev, VMWGFX_NUM_DISPLAY_UNITS);
	else
		ret = drm_vblank_init(dev, 1);
	if (ret != 0)
		goto err_free;

	vmw_kms_create_implicit_placement_property(dev_priv);

	if (dev_priv->capabilities & SVGA_CAP_MULTIMON)
		for (i = 0; i < VMWGFX_NUM_DISPLAY_UNITS; ++i)
			vmw_ldu_init(dev_priv, i);
	else
		vmw_ldu_init(dev_priv, 0);

	dev_priv->active_display_unit = vmw_du_legacy;

	DRM_INFO("Legacy Display Unit initialized\n");

	return 0;

err_free:
	kfree(dev_priv->ldu_priv);
	dev_priv->ldu_priv = NULL;
	return ret;
}