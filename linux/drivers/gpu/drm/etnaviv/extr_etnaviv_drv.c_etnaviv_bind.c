#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct etnaviv_drm_private {struct drm_device* cmdbuf_suballoc; scalar_t__ num_gpus; int /*<<< orphan*/  gem_list; int /*<<< orphan*/  gem_lock; int /*<<< orphan*/  dma_parms; } ;
struct drm_device {struct device* dev; struct etnaviv_drm_private* dev_private; } ;
struct device {int /*<<< orphan*/ * dma_parms; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct drm_device*) ; 
 int PTR_ERR (struct drm_device*) ; 
 int /*<<< orphan*/  SZ_2G ; 
 int component_bind_all (struct device*,struct drm_device*) ; 
 int /*<<< orphan*/  component_unbind_all (struct device*,struct drm_device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct drm_device*) ; 
 int /*<<< orphan*/  dma_set_max_seg_size (struct device*,int /*<<< orphan*/ ) ; 
 struct drm_device* drm_dev_alloc (int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int drm_dev_register (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  etnaviv_cmdbuf_suballoc_destroy (struct drm_device*) ; 
 struct drm_device* etnaviv_cmdbuf_suballoc_new (struct device*) ; 
 int /*<<< orphan*/  etnaviv_drm_driver ; 
 int /*<<< orphan*/  kfree (struct etnaviv_drm_private*) ; 
 struct etnaviv_drm_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_gpu (struct drm_device*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int etnaviv_bind(struct device *dev)
{
	struct etnaviv_drm_private *priv;
	struct drm_device *drm;
	int ret;

	drm = drm_dev_alloc(&etnaviv_drm_driver, dev);
	if (IS_ERR(drm))
		return PTR_ERR(drm);

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv) {
		dev_err(dev, "failed to allocate private data\n");
		ret = -ENOMEM;
		goto out_put;
	}
	drm->dev_private = priv;

	dev->dma_parms = &priv->dma_parms;
	dma_set_max_seg_size(dev, SZ_2G);

	mutex_init(&priv->gem_lock);
	INIT_LIST_HEAD(&priv->gem_list);
	priv->num_gpus = 0;

	priv->cmdbuf_suballoc = etnaviv_cmdbuf_suballoc_new(drm->dev);
	if (IS_ERR(priv->cmdbuf_suballoc)) {
		dev_err(drm->dev, "Failed to create cmdbuf suballocator\n");
		ret = PTR_ERR(priv->cmdbuf_suballoc);
		goto out_free_priv;
	}

	dev_set_drvdata(dev, drm);

	ret = component_bind_all(dev, drm);
	if (ret < 0)
		goto out_destroy_suballoc;

	load_gpu(drm);

	ret = drm_dev_register(drm, 0);
	if (ret)
		goto out_unbind;

	return 0;

out_unbind:
	component_unbind_all(dev, drm);
out_destroy_suballoc:
	etnaviv_cmdbuf_suballoc_destroy(priv->cmdbuf_suballoc);
out_free_priv:
	kfree(priv);
out_put:
	drm_dev_put(drm);

	return ret;
}