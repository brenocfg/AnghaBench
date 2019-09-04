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
struct mtk_dsi {int /*<<< orphan*/  ddp_comp; int /*<<< orphan*/  host; } ;
struct drm_device {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 struct mtk_dsi* dev_get_drvdata (struct device*) ; 
 int mipi_dsi_host_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mipi_dsi_host_unregister (int /*<<< orphan*/ *) ; 
 int mtk_ddp_comp_register (struct drm_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_ddp_comp_unregister (struct drm_device*,int /*<<< orphan*/ *) ; 
 int mtk_dsi_create_conn_enc (struct drm_device*,struct mtk_dsi*) ; 

__attribute__((used)) static int mtk_dsi_bind(struct device *dev, struct device *master, void *data)
{
	int ret;
	struct drm_device *drm = data;
	struct mtk_dsi *dsi = dev_get_drvdata(dev);

	ret = mtk_ddp_comp_register(drm, &dsi->ddp_comp);
	if (ret < 0) {
		dev_err(dev, "Failed to register component %pOF: %d\n",
			dev->of_node, ret);
		return ret;
	}

	ret = mipi_dsi_host_register(&dsi->host);
	if (ret < 0) {
		dev_err(dev, "failed to register DSI host: %d\n", ret);
		goto err_ddp_comp_unregister;
	}

	ret = mtk_dsi_create_conn_enc(drm, dsi);
	if (ret) {
		DRM_ERROR("Encoder create failed with %d\n", ret);
		goto err_unregister;
	}

	return 0;

err_unregister:
	mipi_dsi_host_unregister(&dsi->host);
err_ddp_comp_unregister:
	mtk_ddp_comp_unregister(drm, &dsi->ddp_comp);
	return ret;
}