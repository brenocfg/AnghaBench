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
struct device {int dummy; } ;

/* Variables and functions */
 struct mtk_dsi* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mipi_dsi_host_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_ddp_comp_unregister (struct drm_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_dsi_destroy_conn_enc (struct mtk_dsi*) ; 

__attribute__((used)) static void mtk_dsi_unbind(struct device *dev, struct device *master,
			   void *data)
{
	struct drm_device *drm = data;
	struct mtk_dsi *dsi = dev_get_drvdata(dev);

	mtk_dsi_destroy_conn_enc(dsi);
	mipi_dsi_host_unregister(&dsi->host);
	mtk_ddp_comp_unregister(drm, &dsi->ddp_comp);
}