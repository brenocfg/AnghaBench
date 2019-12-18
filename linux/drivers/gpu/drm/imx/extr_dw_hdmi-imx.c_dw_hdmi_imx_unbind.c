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
struct imx_hdmi {int /*<<< orphan*/  hdmi; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct imx_hdmi* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dw_hdmi_unbind (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dw_hdmi_imx_unbind(struct device *dev, struct device *master,
			       void *data)
{
	struct imx_hdmi *hdmi = dev_get_drvdata(dev);

	dw_hdmi_unbind(hdmi->hdmi);
}