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
struct vc4_hdmi {TYPE_1__* ddc; int /*<<< orphan*/  hsm_clock; int /*<<< orphan*/  encoder; int /*<<< orphan*/  connector; int /*<<< orphan*/  cec_adap; } ;
struct vc4_dev {struct vc4_hdmi* hdmi; } ;
struct drm_device {struct vc4_dev* dev_private; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cec_unregister_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct drm_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc4_hdmi_connector_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc4_hdmi_encoder_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vc4_hdmi_unbind(struct device *dev, struct device *master,
			    void *data)
{
	struct drm_device *drm = dev_get_drvdata(master);
	struct vc4_dev *vc4 = drm->dev_private;
	struct vc4_hdmi *hdmi = vc4->hdmi;

	cec_unregister_adapter(hdmi->cec_adap);
	vc4_hdmi_connector_destroy(hdmi->connector);
	vc4_hdmi_encoder_destroy(hdmi->encoder);

	clk_disable_unprepare(hdmi->hsm_clock);
	pm_runtime_disable(dev);

	put_device(&hdmi->ddc->dev);

	vc4->hdmi = NULL;
}