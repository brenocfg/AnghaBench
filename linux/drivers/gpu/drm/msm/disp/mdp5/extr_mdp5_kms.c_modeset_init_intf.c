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
struct msm_drm_private {int /*<<< orphan*/ * dsi; int /*<<< orphan*/  hdmi; int /*<<< orphan*/  edp; } ;
struct mdp5_kms {int /*<<< orphan*/  cfg; struct mdp5_ctl_manager* ctlm; struct drm_device* dev; } ;
struct mdp5_interface {int type; int num; } ;
struct mdp5_ctl_manager {int dummy; } ;
struct mdp5_ctl {int dummy; } ;
struct mdp5_cfg_hw {int dummy; } ;
struct drm_encoder {int dummy; } ;
struct drm_device {int /*<<< orphan*/  dev; struct msm_drm_private* dev_private; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int EINVAL ; 
#define  INTF_DSI 130 
#define  INTF_HDMI 129 
#define  INTF_eDP 128 
 int /*<<< orphan*/  IS_ERR (struct drm_encoder*) ; 
 int PTR_ERR (struct drm_encoder*) ; 
 struct drm_encoder* construct_encoder (struct mdp5_kms*,struct mdp5_interface*,struct mdp5_ctl*) ; 
 int get_dsi_id_from_intf (struct mdp5_cfg_hw const*,int) ; 
 struct mdp5_cfg_hw* mdp5_cfg_get_hw_config (int /*<<< orphan*/ ) ; 
 struct mdp5_ctl* mdp5_ctlm_request (struct mdp5_ctl_manager*,int) ; 
 int msm_dsi_modeset_init (int /*<<< orphan*/ ,struct drm_device*,struct drm_encoder*) ; 
 int msm_edp_modeset_init (int /*<<< orphan*/ ,struct drm_device*,struct drm_encoder*) ; 
 int msm_hdmi_modeset_init (int /*<<< orphan*/ ,struct drm_device*,struct drm_encoder*) ; 

__attribute__((used)) static int modeset_init_intf(struct mdp5_kms *mdp5_kms,
			     struct mdp5_interface *intf)
{
	struct drm_device *dev = mdp5_kms->dev;
	struct msm_drm_private *priv = dev->dev_private;
	struct mdp5_ctl_manager *ctlm = mdp5_kms->ctlm;
	struct mdp5_ctl *ctl;
	struct drm_encoder *encoder;
	int ret = 0;

	switch (intf->type) {
	case INTF_eDP:
		if (!priv->edp)
			break;

		ctl = mdp5_ctlm_request(ctlm, intf->num);
		if (!ctl) {
			ret = -EINVAL;
			break;
		}

		encoder = construct_encoder(mdp5_kms, intf, ctl);
		if (IS_ERR(encoder)) {
			ret = PTR_ERR(encoder);
			break;
		}

		ret = msm_edp_modeset_init(priv->edp, dev, encoder);
		break;
	case INTF_HDMI:
		if (!priv->hdmi)
			break;

		ctl = mdp5_ctlm_request(ctlm, intf->num);
		if (!ctl) {
			ret = -EINVAL;
			break;
		}

		encoder = construct_encoder(mdp5_kms, intf, ctl);
		if (IS_ERR(encoder)) {
			ret = PTR_ERR(encoder);
			break;
		}

		ret = msm_hdmi_modeset_init(priv->hdmi, dev, encoder);
		break;
	case INTF_DSI:
	{
		const struct mdp5_cfg_hw *hw_cfg =
					mdp5_cfg_get_hw_config(mdp5_kms->cfg);
		int dsi_id = get_dsi_id_from_intf(hw_cfg, intf->num);

		if ((dsi_id >= ARRAY_SIZE(priv->dsi)) || (dsi_id < 0)) {
			DRM_DEV_ERROR(dev->dev, "failed to find dsi from intf %d\n",
				intf->num);
			ret = -EINVAL;
			break;
		}

		if (!priv->dsi[dsi_id])
			break;

		ctl = mdp5_ctlm_request(ctlm, intf->num);
		if (!ctl) {
			ret = -EINVAL;
			break;
		}

		encoder = construct_encoder(mdp5_kms, intf, ctl);
		if (IS_ERR(encoder)) {
			ret = PTR_ERR(encoder);
			break;
		}

		ret = msm_dsi_modeset_init(priv->dsi[dsi_id], dev, encoder);
		break;
	}
	default:
		DRM_DEV_ERROR(dev->dev, "unknown intf: %d\n", intf->type);
		ret = -EINVAL;
		break;
	}

	return ret;
}