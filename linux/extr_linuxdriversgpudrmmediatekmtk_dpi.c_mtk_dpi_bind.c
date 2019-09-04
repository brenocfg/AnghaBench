#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  possible_crtcs; } ;
struct mtk_dpi {int /*<<< orphan*/  ddp_comp; TYPE_1__ encoder; int /*<<< orphan*/  color_format; int /*<<< orphan*/  yc_map; int /*<<< orphan*/  channel_swap; int /*<<< orphan*/  bit_num; int /*<<< orphan*/  bridge; } ;
struct drm_device {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_TMDS ; 
 int /*<<< orphan*/  MTK_DPI_COLOR_FORMAT_RGB ; 
 int /*<<< orphan*/  MTK_DPI_OUT_BIT_NUM_8BITS ; 
 int /*<<< orphan*/  MTK_DPI_OUT_CHANNEL_SWAP_RGB ; 
 int /*<<< orphan*/  MTK_DPI_OUT_YC_MAP_RGB ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 struct mtk_dpi* dev_get_drvdata (struct device*) ; 
 int drm_bridge_attach (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_encoder_helper_add (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int drm_encoder_init (struct drm_device*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mtk_ddp_comp_register (struct drm_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_ddp_comp_unregister (struct drm_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_dpi_encoder_funcs ; 
 int /*<<< orphan*/  mtk_dpi_encoder_helper_funcs ; 

__attribute__((used)) static int mtk_dpi_bind(struct device *dev, struct device *master, void *data)
{
	struct mtk_dpi *dpi = dev_get_drvdata(dev);
	struct drm_device *drm_dev = data;
	int ret;

	ret = mtk_ddp_comp_register(drm_dev, &dpi->ddp_comp);
	if (ret < 0) {
		dev_err(dev, "Failed to register component %pOF: %d\n",
			dev->of_node, ret);
		return ret;
	}

	ret = drm_encoder_init(drm_dev, &dpi->encoder, &mtk_dpi_encoder_funcs,
			       DRM_MODE_ENCODER_TMDS, NULL);
	if (ret) {
		dev_err(dev, "Failed to initialize decoder: %d\n", ret);
		goto err_unregister;
	}
	drm_encoder_helper_add(&dpi->encoder, &mtk_dpi_encoder_helper_funcs);

	/* Currently DPI0 is fixed to be driven by OVL1 */
	dpi->encoder.possible_crtcs = BIT(1);

	ret = drm_bridge_attach(&dpi->encoder, dpi->bridge, NULL);
	if (ret) {
		dev_err(dev, "Failed to attach bridge: %d\n", ret);
		goto err_cleanup;
	}

	dpi->bit_num = MTK_DPI_OUT_BIT_NUM_8BITS;
	dpi->channel_swap = MTK_DPI_OUT_CHANNEL_SWAP_RGB;
	dpi->yc_map = MTK_DPI_OUT_YC_MAP_RGB;
	dpi->color_format = MTK_DPI_COLOR_FORMAT_RGB;

	return 0;

err_cleanup:
	drm_encoder_cleanup(&dpi->encoder);
err_unregister:
	mtk_ddp_comp_unregister(drm_dev, &dpi->ddp_comp);
	return ret;
}