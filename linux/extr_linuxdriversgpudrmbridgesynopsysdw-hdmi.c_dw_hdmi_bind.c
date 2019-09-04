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
struct platform_device {int dummy; } ;
struct dw_hdmi_plat_data {int dummy; } ;
struct dw_hdmi {int /*<<< orphan*/  bridge; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 struct dw_hdmi* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct dw_hdmi*) ; 
 struct dw_hdmi* __dw_hdmi_probe (struct platform_device*,struct dw_hdmi_plat_data const*) ; 
 int drm_bridge_attach (struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dw_hdmi_remove (struct dw_hdmi*) ; 

struct dw_hdmi *dw_hdmi_bind(struct platform_device *pdev,
			     struct drm_encoder *encoder,
			     const struct dw_hdmi_plat_data *plat_data)
{
	struct dw_hdmi *hdmi;
	int ret;

	hdmi = __dw_hdmi_probe(pdev, plat_data);
	if (IS_ERR(hdmi))
		return hdmi;

	ret = drm_bridge_attach(encoder, &hdmi->bridge, NULL);
	if (ret) {
		dw_hdmi_remove(hdmi);
		DRM_ERROR("Failed to initialize bridge with drm\n");
		return ERR_PTR(ret);
	}

	return hdmi;
}