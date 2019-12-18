#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tilcdc_drm_private {struct drm_crtc* crtc; scalar_t__ is_componentized; } ;
struct drm_crtc {int /*<<< orphan*/  port; } ;
struct tilcdc_crtc {int /*<<< orphan*/  primary; int /*<<< orphan*/  recover_work; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  frame_done_wq; int /*<<< orphan*/  enable_lock; struct drm_crtc base; int /*<<< orphan*/ * palette_base; int /*<<< orphan*/  palette_dma_handle; int /*<<< orphan*/  palette_loaded; } ;
struct drm_device {TYPE_1__* dev; struct tilcdc_drm_private* dev_private; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TILCDC_PALETTE_FIRST_ENTRY ; 
 int /*<<< orphan*/  TILCDC_PALETTE_SIZE ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 struct tilcdc_crtc* devm_kzalloc (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/ * dmam_alloc_coherent (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  drm_crtc_helper_add (struct drm_crtc*,int /*<<< orphan*/ *) ; 
 int drm_crtc_init_with_planes (struct drm_device*,struct drm_crtc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_graph_get_port_by_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tilcdc_crtc_destroy (struct drm_crtc*) ; 
 int /*<<< orphan*/  tilcdc_crtc_funcs ; 
 int /*<<< orphan*/  tilcdc_crtc_helper_funcs ; 
 int /*<<< orphan*/  tilcdc_crtc_recover_work ; 
 int tilcdc_plane_init (struct drm_device*,int /*<<< orphan*/ *) ; 

int tilcdc_crtc_create(struct drm_device *dev)
{
	struct tilcdc_drm_private *priv = dev->dev_private;
	struct tilcdc_crtc *tilcdc_crtc;
	struct drm_crtc *crtc;
	int ret;

	tilcdc_crtc = devm_kzalloc(dev->dev, sizeof(*tilcdc_crtc), GFP_KERNEL);
	if (!tilcdc_crtc)
		return -ENOMEM;

	init_completion(&tilcdc_crtc->palette_loaded);
	tilcdc_crtc->palette_base = dmam_alloc_coherent(dev->dev,
					TILCDC_PALETTE_SIZE,
					&tilcdc_crtc->palette_dma_handle,
					GFP_KERNEL | __GFP_ZERO);
	if (!tilcdc_crtc->palette_base)
		return -ENOMEM;
	*tilcdc_crtc->palette_base = TILCDC_PALETTE_FIRST_ENTRY;

	crtc = &tilcdc_crtc->base;

	ret = tilcdc_plane_init(dev, &tilcdc_crtc->primary);
	if (ret < 0)
		goto fail;

	mutex_init(&tilcdc_crtc->enable_lock);

	init_waitqueue_head(&tilcdc_crtc->frame_done_wq);

	spin_lock_init(&tilcdc_crtc->irq_lock);
	INIT_WORK(&tilcdc_crtc->recover_work, tilcdc_crtc_recover_work);

	ret = drm_crtc_init_with_planes(dev, crtc,
					&tilcdc_crtc->primary,
					NULL,
					&tilcdc_crtc_funcs,
					"tilcdc crtc");
	if (ret < 0)
		goto fail;

	drm_crtc_helper_add(crtc, &tilcdc_crtc_helper_funcs);

	if (priv->is_componentized) {
		crtc->port = of_graph_get_port_by_id(dev->dev->of_node, 0);
		if (!crtc->port) { /* This should never happen */
			dev_err(dev->dev, "Port node not found in %pOF\n",
				dev->dev->of_node);
			ret = -EINVAL;
			goto fail;
		}
	}

	priv->crtc = crtc;
	return 0;

fail:
	tilcdc_crtc_destroy(crtc);
	return ret;
}