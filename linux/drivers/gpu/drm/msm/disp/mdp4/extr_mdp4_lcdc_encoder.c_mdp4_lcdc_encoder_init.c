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
struct regulator {int dummy; } ;
struct drm_encoder {int dummy; } ;
struct mdp4_lcdc_encoder {struct regulator** regs; struct regulator* lcdc_clk; struct drm_encoder base; struct device_node* panel_node; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_LVDS ; 
 int ENOMEM ; 
 struct drm_encoder* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regulator*) ; 
 int PTR_ERR (struct regulator*) ; 
 int /*<<< orphan*/  bs_init (struct mdp4_lcdc_encoder*) ; 
 struct regulator* devm_regulator_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  drm_encoder_helper_add (struct drm_encoder*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mdp4_lcdc_encoder* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdp4_lcdc_encoder_destroy (struct drm_encoder*) ; 
 int /*<<< orphan*/  mdp4_lcdc_encoder_funcs ; 
 int /*<<< orphan*/  mdp4_lcdc_encoder_helper_funcs ; 
 struct regulator* mpd4_lvds_pll_init (struct drm_device*) ; 

struct drm_encoder *mdp4_lcdc_encoder_init(struct drm_device *dev,
		struct device_node *panel_node)
{
	struct drm_encoder *encoder = NULL;
	struct mdp4_lcdc_encoder *mdp4_lcdc_encoder;
	struct regulator *reg;
	int ret;

	mdp4_lcdc_encoder = kzalloc(sizeof(*mdp4_lcdc_encoder), GFP_KERNEL);
	if (!mdp4_lcdc_encoder) {
		ret = -ENOMEM;
		goto fail;
	}

	mdp4_lcdc_encoder->panel_node = panel_node;

	encoder = &mdp4_lcdc_encoder->base;

	drm_encoder_init(dev, encoder, &mdp4_lcdc_encoder_funcs,
			 DRM_MODE_ENCODER_LVDS, NULL);
	drm_encoder_helper_add(encoder, &mdp4_lcdc_encoder_helper_funcs);

	/* TODO: do we need different pll in other cases? */
	mdp4_lcdc_encoder->lcdc_clk = mpd4_lvds_pll_init(dev);
	if (IS_ERR(mdp4_lcdc_encoder->lcdc_clk)) {
		DRM_DEV_ERROR(dev->dev, "failed to get lvds_clk\n");
		ret = PTR_ERR(mdp4_lcdc_encoder->lcdc_clk);
		goto fail;
	}

	/* TODO: different regulators in other cases? */
	reg = devm_regulator_get(dev->dev, "lvds-vccs-3p3v");
	if (IS_ERR(reg)) {
		ret = PTR_ERR(reg);
		DRM_DEV_ERROR(dev->dev, "failed to get lvds-vccs-3p3v: %d\n", ret);
		goto fail;
	}
	mdp4_lcdc_encoder->regs[0] = reg;

	reg = devm_regulator_get(dev->dev, "lvds-pll-vdda");
	if (IS_ERR(reg)) {
		ret = PTR_ERR(reg);
		DRM_DEV_ERROR(dev->dev, "failed to get lvds-pll-vdda: %d\n", ret);
		goto fail;
	}
	mdp4_lcdc_encoder->regs[1] = reg;

	reg = devm_regulator_get(dev->dev, "lvds-vdda");
	if (IS_ERR(reg)) {
		ret = PTR_ERR(reg);
		DRM_DEV_ERROR(dev->dev, "failed to get lvds-vdda: %d\n", ret);
		goto fail;
	}
	mdp4_lcdc_encoder->regs[2] = reg;

	bs_init(mdp4_lcdc_encoder);

	return encoder;

fail:
	if (encoder)
		mdp4_lcdc_encoder_destroy(encoder);

	return ERR_PTR(ret);
}