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
struct mtk_drm_private {int num_pipes; struct mtk_ddp_comp** ddp_comp; struct device_node** comp_node; int /*<<< orphan*/  mutex_dev; int /*<<< orphan*/  config_regs; } ;
struct mtk_drm_crtc {unsigned int ddp_comp_nr; unsigned int layer_nr; int /*<<< orphan*/  base; int /*<<< orphan*/ * planes; struct mtk_ddp_comp** ddp_comp; int /*<<< orphan*/  mutex; int /*<<< orphan*/  config_regs; } ;
struct mtk_ddp_comp {int dummy; } ;
struct drm_plane {int dummy; } ;
struct drm_device {struct device* dev; struct mtk_drm_private* dev_private; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
typedef  enum mtk_ddp_comp_id { ____Placeholder_mtk_ddp_comp_id } mtk_ddp_comp_id ;
typedef  enum drm_plane_type { ____Placeholder_drm_plane_type } drm_plane_type ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int DRM_PLANE_TYPE_CURSOR ; 
 int DRM_PLANE_TYPE_OVERLAY ; 
 int DRM_PLANE_TYPE_PRIMARY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTK_LUT_SIZE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int,int) ; 
 int /*<<< orphan*/ * devm_kcalloc (struct device*,unsigned int,int,int /*<<< orphan*/ ) ; 
 struct mtk_ddp_comp** devm_kmalloc_array (struct device*,unsigned int,int,int /*<<< orphan*/ ) ; 
 struct mtk_drm_crtc* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_crtc_enable_color_mgmt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_crtc_set_gamma_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int mtk_ddp_comp_layer_nr (struct mtk_ddp_comp*) ; 
 int /*<<< orphan*/  mtk_disp_mutex_get (int /*<<< orphan*/ ,int) ; 
 int mtk_drm_crtc_init (struct drm_device*,struct mtk_drm_crtc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int mtk_plane_init (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int mtk_drm_crtc_create(struct drm_device *drm_dev,
			const enum mtk_ddp_comp_id *path, unsigned int path_len)
{
	struct mtk_drm_private *priv = drm_dev->dev_private;
	struct device *dev = drm_dev->dev;
	struct mtk_drm_crtc *mtk_crtc;
	enum drm_plane_type type;
	unsigned int zpos;
	int pipe = priv->num_pipes;
	int ret;
	int i;

	if (!path)
		return 0;

	for (i = 0; i < path_len; i++) {
		enum mtk_ddp_comp_id comp_id = path[i];
		struct device_node *node;

		node = priv->comp_node[comp_id];
		if (!node) {
			dev_info(dev,
				 "Not creating crtc %d because component %d is disabled or missing\n",
				 pipe, comp_id);
			return 0;
		}
	}

	mtk_crtc = devm_kzalloc(dev, sizeof(*mtk_crtc), GFP_KERNEL);
	if (!mtk_crtc)
		return -ENOMEM;

	mtk_crtc->config_regs = priv->config_regs;
	mtk_crtc->ddp_comp_nr = path_len;
	mtk_crtc->ddp_comp = devm_kmalloc_array(dev, mtk_crtc->ddp_comp_nr,
						sizeof(*mtk_crtc->ddp_comp),
						GFP_KERNEL);
	if (!mtk_crtc->ddp_comp)
		return -ENOMEM;

	mtk_crtc->mutex = mtk_disp_mutex_get(priv->mutex_dev, pipe);
	if (IS_ERR(mtk_crtc->mutex)) {
		ret = PTR_ERR(mtk_crtc->mutex);
		dev_err(dev, "Failed to get mutex: %d\n", ret);
		return ret;
	}

	for (i = 0; i < mtk_crtc->ddp_comp_nr; i++) {
		enum mtk_ddp_comp_id comp_id = path[i];
		struct mtk_ddp_comp *comp;
		struct device_node *node;

		node = priv->comp_node[comp_id];
		comp = priv->ddp_comp[comp_id];
		if (!comp) {
			dev_err(dev, "Component %pOF not initialized\n", node);
			ret = -ENODEV;
			return ret;
		}

		mtk_crtc->ddp_comp[i] = comp;
	}

	mtk_crtc->layer_nr = mtk_ddp_comp_layer_nr(mtk_crtc->ddp_comp[0]);
	mtk_crtc->planes = devm_kcalloc(dev, mtk_crtc->layer_nr,
					sizeof(struct drm_plane),
					GFP_KERNEL);

	for (zpos = 0; zpos < mtk_crtc->layer_nr; zpos++) {
		type = (zpos == 0) ? DRM_PLANE_TYPE_PRIMARY :
				(zpos == 1) ? DRM_PLANE_TYPE_CURSOR :
						DRM_PLANE_TYPE_OVERLAY;
		ret = mtk_plane_init(drm_dev, &mtk_crtc->planes[zpos],
				     BIT(pipe), type);
		if (ret)
			return ret;
	}

	ret = mtk_drm_crtc_init(drm_dev, mtk_crtc, &mtk_crtc->planes[0],
				mtk_crtc->layer_nr > 1 ? &mtk_crtc->planes[1] :
				NULL, pipe);
	if (ret < 0)
		return ret;
	drm_mode_crtc_set_gamma_size(&mtk_crtc->base, MTK_LUT_SIZE);
	drm_crtc_enable_color_mgmt(&mtk_crtc->base, 0, false, MTK_LUT_SIZE);
	priv->num_pipes++;

	return 0;
}