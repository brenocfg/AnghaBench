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
struct sun6i_dsi {int /*<<< orphan*/  panel; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct sun6i_dsi* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  drm_panel_detach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sun6i_dsi_unbind(struct device *dev, struct device *master,
			    void *data)
{
	struct sun6i_dsi *dsi = dev_get_drvdata(dev);

	drm_panel_detach(dsi->panel);
}