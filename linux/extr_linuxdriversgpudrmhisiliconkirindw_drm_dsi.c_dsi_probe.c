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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct dw_dsi {struct dsi_hw_ctx* ctx; } ;
struct dsi_hw_ctx {int dummy; } ;
struct dsi_data {struct dsi_hw_ctx ctx; struct dw_dsi dsi; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int component_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct dsi_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_ops ; 
 int dsi_parse_dt (struct platform_device*,struct dw_dsi*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct dsi_data*) ; 

__attribute__((used)) static int dsi_probe(struct platform_device *pdev)
{
	struct dsi_data *data;
	struct dw_dsi *dsi;
	struct dsi_hw_ctx *ctx;
	int ret;

	data = devm_kzalloc(&pdev->dev, sizeof(*data), GFP_KERNEL);
	if (!data) {
		DRM_ERROR("failed to allocate dsi data.\n");
		return -ENOMEM;
	}
	dsi = &data->dsi;
	ctx = &data->ctx;
	dsi->ctx = ctx;

	ret = dsi_parse_dt(pdev, dsi);
	if (ret)
		return ret;

	platform_set_drvdata(pdev, data);

	return component_add(&pdev->dev, &dsi_ops);
}