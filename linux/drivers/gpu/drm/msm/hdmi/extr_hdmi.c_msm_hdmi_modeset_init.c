#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_8__ dev; } ;
struct msm_drm_private {int /*<<< orphan*/  num_connectors; TYPE_3__** connectors; int /*<<< orphan*/  num_bridges; TYPE_3__** bridges; } ;
struct TYPE_12__ {int /*<<< orphan*/  infoframe; } ;
struct hdmi {int irq; TYPE_3__* connector; TYPE_3__* bridge; struct platform_device* pdev; TYPE_1__ audio; struct drm_encoder* encoder; struct drm_device* dev; } ;
struct drm_encoder {TYPE_3__* bridge; } ;
struct drm_device {TYPE_8__* dev; struct msm_drm_private* dev_private; } ;
struct TYPE_14__ {TYPE_2__* funcs; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* destroy ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (TYPE_8__*,char*,int,...) ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_HIGH ; 
 scalar_t__ IS_ERR (TYPE_3__*) ; 
 int PTR_ERR (TYPE_3__*) ; 
 int devm_request_irq (TYPE_8__*,int,int /*<<< orphan*/ ,int,char*,struct hdmi*) ; 
 int /*<<< orphan*/  hdmi_audio_infoframe_init (int /*<<< orphan*/ *) ; 
 int irq_of_parse_and_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_hdmi_bridge_destroy (TYPE_3__*) ; 
 TYPE_3__* msm_hdmi_bridge_init (struct hdmi*) ; 
 TYPE_3__* msm_hdmi_connector_init (struct hdmi*) ; 
 int msm_hdmi_hpd_enable (TYPE_3__*) ; 
 int /*<<< orphan*/  msm_hdmi_irq ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct hdmi*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

int msm_hdmi_modeset_init(struct hdmi *hdmi,
		struct drm_device *dev, struct drm_encoder *encoder)
{
	struct msm_drm_private *priv = dev->dev_private;
	struct platform_device *pdev = hdmi->pdev;
	int ret;

	hdmi->dev = dev;
	hdmi->encoder = encoder;

	hdmi_audio_infoframe_init(&hdmi->audio.infoframe);

	hdmi->bridge = msm_hdmi_bridge_init(hdmi);
	if (IS_ERR(hdmi->bridge)) {
		ret = PTR_ERR(hdmi->bridge);
		DRM_DEV_ERROR(dev->dev, "failed to create HDMI bridge: %d\n", ret);
		hdmi->bridge = NULL;
		goto fail;
	}

	hdmi->connector = msm_hdmi_connector_init(hdmi);
	if (IS_ERR(hdmi->connector)) {
		ret = PTR_ERR(hdmi->connector);
		DRM_DEV_ERROR(dev->dev, "failed to create HDMI connector: %d\n", ret);
		hdmi->connector = NULL;
		goto fail;
	}

	hdmi->irq = irq_of_parse_and_map(pdev->dev.of_node, 0);
	if (hdmi->irq < 0) {
		ret = hdmi->irq;
		DRM_DEV_ERROR(dev->dev, "failed to get irq: %d\n", ret);
		goto fail;
	}

	ret = devm_request_irq(&pdev->dev, hdmi->irq,
			msm_hdmi_irq, IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
			"hdmi_isr", hdmi);
	if (ret < 0) {
		DRM_DEV_ERROR(dev->dev, "failed to request IRQ%u: %d\n",
				hdmi->irq, ret);
		goto fail;
	}

	ret = msm_hdmi_hpd_enable(hdmi->connector);
	if (ret < 0) {
		DRM_DEV_ERROR(&hdmi->pdev->dev, "failed to enable HPD: %d\n", ret);
		goto fail;
	}

	encoder->bridge = hdmi->bridge;

	priv->bridges[priv->num_bridges++]       = hdmi->bridge;
	priv->connectors[priv->num_connectors++] = hdmi->connector;

	platform_set_drvdata(pdev, hdmi);

	return 0;

fail:
	/* bridge is normally destroyed by drm: */
	if (hdmi->bridge) {
		msm_hdmi_bridge_destroy(hdmi->bridge);
		hdmi->bridge = NULL;
	}
	if (hdmi->connector) {
		hdmi->connector->funcs->destroy(hdmi->connector);
		hdmi->connector = NULL;
	}

	return ret;
}