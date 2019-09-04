#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct drm_encoder {scalar_t__ possible_crtcs; } ;
struct dw_hdmi_plat_data {char* phy_name; int /*<<< orphan*/  phy_data; int /*<<< orphan*/  phy_ops; int /*<<< orphan*/ * mode_valid; } ;
struct sun8i_dw_hdmi {int /*<<< orphan*/  rst_ctrl; int /*<<< orphan*/  clk_tmds; int /*<<< orphan*/  hdmi; int /*<<< orphan*/  phy; struct drm_encoder encoder; TYPE_1__* dev; struct dw_hdmi_plat_data plat_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct drm_device {int dummy; } ;
struct device_node {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_ENCODER_TMDS ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,char*) ; 
 struct sun8i_dw_hdmi* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_reset_control_get (struct device*,char*) ; 
 int /*<<< orphan*/  drm_encoder_cleanup (struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_encoder_helper_add (struct drm_encoder*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dw_hdmi_bind (struct platform_device*,struct drm_encoder*,struct dw_hdmi_plat_data*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sun8i_dw_hdmi*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun8i_dw_hdmi_encoder_funcs ; 
 int /*<<< orphan*/  sun8i_dw_hdmi_encoder_helper_funcs ; 
 scalar_t__ sun8i_dw_hdmi_find_possible_crtcs (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun8i_dw_hdmi_mode_valid ; 
 int /*<<< orphan*/  sun8i_hdmi_phy_get_ops () ; 
 int /*<<< orphan*/  sun8i_hdmi_phy_init (int /*<<< orphan*/ ) ; 
 int sun8i_hdmi_phy_probe (struct sun8i_dw_hdmi*,struct device_node*) ; 
 int /*<<< orphan*/  sun8i_hdmi_phy_remove (struct sun8i_dw_hdmi*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int sun8i_dw_hdmi_bind(struct device *dev, struct device *master,
			      void *data)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct dw_hdmi_plat_data *plat_data;
	struct drm_device *drm = data;
	struct device_node *phy_node;
	struct drm_encoder *encoder;
	struct sun8i_dw_hdmi *hdmi;
	int ret;

	if (!pdev->dev.of_node)
		return -ENODEV;

	hdmi = devm_kzalloc(&pdev->dev, sizeof(*hdmi), GFP_KERNEL);
	if (!hdmi)
		return -ENOMEM;

	plat_data = &hdmi->plat_data;
	hdmi->dev = &pdev->dev;
	encoder = &hdmi->encoder;

	encoder->possible_crtcs =
		sun8i_dw_hdmi_find_possible_crtcs(drm, dev->of_node);
	/*
	 * If we failed to find the CRTC(s) which this encoder is
	 * supposed to be connected to, it's because the CRTC has
	 * not been registered yet.  Defer probing, and hope that
	 * the required CRTC is added later.
	 */
	if (encoder->possible_crtcs == 0)
		return -EPROBE_DEFER;

	hdmi->rst_ctrl = devm_reset_control_get(dev, "ctrl");
	if (IS_ERR(hdmi->rst_ctrl)) {
		dev_err(dev, "Could not get ctrl reset control\n");
		return PTR_ERR(hdmi->rst_ctrl);
	}

	hdmi->clk_tmds = devm_clk_get(dev, "tmds");
	if (IS_ERR(hdmi->clk_tmds)) {
		dev_err(dev, "Couldn't get the tmds clock\n");
		return PTR_ERR(hdmi->clk_tmds);
	}

	ret = reset_control_deassert(hdmi->rst_ctrl);
	if (ret) {
		dev_err(dev, "Could not deassert ctrl reset control\n");
		return ret;
	}

	ret = clk_prepare_enable(hdmi->clk_tmds);
	if (ret) {
		dev_err(dev, "Could not enable tmds clock\n");
		goto err_assert_ctrl_reset;
	}

	phy_node = of_parse_phandle(dev->of_node, "phys", 0);
	if (!phy_node) {
		dev_err(dev, "Can't found PHY phandle\n");
		goto err_disable_clk_tmds;
	}

	ret = sun8i_hdmi_phy_probe(hdmi, phy_node);
	of_node_put(phy_node);
	if (ret) {
		dev_err(dev, "Couldn't get the HDMI PHY\n");
		goto err_disable_clk_tmds;
	}

	drm_encoder_helper_add(encoder, &sun8i_dw_hdmi_encoder_helper_funcs);
	drm_encoder_init(drm, encoder, &sun8i_dw_hdmi_encoder_funcs,
			 DRM_MODE_ENCODER_TMDS, NULL);

	sun8i_hdmi_phy_init(hdmi->phy);

	plat_data->mode_valid = &sun8i_dw_hdmi_mode_valid;
	plat_data->phy_ops = sun8i_hdmi_phy_get_ops();
	plat_data->phy_name = "sun8i_dw_hdmi_phy";
	plat_data->phy_data = hdmi->phy;

	platform_set_drvdata(pdev, hdmi);

	hdmi->hdmi = dw_hdmi_bind(pdev, encoder, plat_data);

	/*
	 * If dw_hdmi_bind() fails we'll never call dw_hdmi_unbind(),
	 * which would have called the encoder cleanup.  Do it manually.
	 */
	if (IS_ERR(hdmi->hdmi)) {
		ret = PTR_ERR(hdmi->hdmi);
		goto cleanup_encoder;
	}

	return 0;

cleanup_encoder:
	drm_encoder_cleanup(encoder);
	sun8i_hdmi_phy_remove(hdmi);
err_disable_clk_tmds:
	clk_disable_unprepare(hdmi->clk_tmds);
err_assert_ctrl_reset:
	reset_control_assert(hdmi->rst_ctrl);

	return ret;
}