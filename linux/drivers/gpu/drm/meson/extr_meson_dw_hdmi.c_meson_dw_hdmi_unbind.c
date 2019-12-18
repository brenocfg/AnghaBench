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
struct meson_dw_hdmi {int /*<<< orphan*/  hdmi; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct meson_dw_hdmi* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dw_hdmi_unbind (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void meson_dw_hdmi_unbind(struct device *dev, struct device *master,
				   void *data)
{
	struct meson_dw_hdmi *meson_dw_hdmi = dev_get_drvdata(dev);

	dw_hdmi_unbind(meson_dw_hdmi->hdmi);
}