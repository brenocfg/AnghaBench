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

/* Variables and functions */
 scalar_t__ IS_ERR (struct dw_hdmi*) ; 
 struct dw_hdmi* __dw_hdmi_probe (struct platform_device*,struct dw_hdmi_plat_data const*) ; 
 int /*<<< orphan*/  drm_bridge_add (int /*<<< orphan*/ *) ; 

struct dw_hdmi *dw_hdmi_probe(struct platform_device *pdev,
			      const struct dw_hdmi_plat_data *plat_data)
{
	struct dw_hdmi *hdmi;

	hdmi = __dw_hdmi_probe(pdev, plat_data);
	if (IS_ERR(hdmi))
		return hdmi;

	drm_bridge_add(&hdmi->bridge);

	return hdmi;
}