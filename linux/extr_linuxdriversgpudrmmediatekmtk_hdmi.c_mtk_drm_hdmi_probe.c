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
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/ * funcs; } ;
struct mtk_hdmi {TYPE_1__ bridge; int /*<<< orphan*/  phy; struct device* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct mtk_hdmi* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_phy_get (struct device*,char*) ; 
 int /*<<< orphan*/  drm_bridge_add (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_bridge_remove (TYPE_1__*) ; 
 int /*<<< orphan*/  mtk_hdmi_bridge_funcs ; 
 int mtk_hdmi_clk_enable_audio (struct mtk_hdmi*) ; 
 int mtk_hdmi_dt_parse_pdata (struct mtk_hdmi*,struct platform_device*) ; 
 int mtk_hdmi_output_init (struct mtk_hdmi*) ; 
 int /*<<< orphan*/  mtk_hdmi_register_audio_driver (struct device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mtk_hdmi*) ; 

__attribute__((used)) static int mtk_drm_hdmi_probe(struct platform_device *pdev)
{
	struct mtk_hdmi *hdmi;
	struct device *dev = &pdev->dev;
	int ret;

	hdmi = devm_kzalloc(dev, sizeof(*hdmi), GFP_KERNEL);
	if (!hdmi)
		return -ENOMEM;

	hdmi->dev = dev;

	ret = mtk_hdmi_dt_parse_pdata(hdmi, pdev);
	if (ret)
		return ret;

	hdmi->phy = devm_phy_get(dev, "hdmi");
	if (IS_ERR(hdmi->phy)) {
		ret = PTR_ERR(hdmi->phy);
		dev_err(dev, "Failed to get HDMI PHY: %d\n", ret);
		return ret;
	}

	platform_set_drvdata(pdev, hdmi);

	ret = mtk_hdmi_output_init(hdmi);
	if (ret) {
		dev_err(dev, "Failed to initialize hdmi output\n");
		return ret;
	}

	mtk_hdmi_register_audio_driver(dev);

	hdmi->bridge.funcs = &mtk_hdmi_bridge_funcs;
	hdmi->bridge.of_node = pdev->dev.of_node;
	drm_bridge_add(&hdmi->bridge);

	ret = mtk_hdmi_clk_enable_audio(hdmi);
	if (ret) {
		dev_err(dev, "Failed to enable audio clocks: %d\n", ret);
		goto err_bridge_remove;
	}

	dev_dbg(dev, "mediatek hdmi probe success\n");
	return 0;

err_bridge_remove:
	drm_bridge_remove(&hdmi->bridge);
	return ret;
}