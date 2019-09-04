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
struct imx_parallel_display {int /*<<< orphan*/  edid; scalar_t__ panel; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct imx_parallel_display* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  drm_panel_detach (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void imx_pd_unbind(struct device *dev, struct device *master,
	void *data)
{
	struct imx_parallel_display *imxpd = dev_get_drvdata(dev);

	if (imxpd->panel)
		drm_panel_detach(imxpd->panel);

	kfree(imxpd->edid);
}