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
struct imx_ldb_channel {int /*<<< orphan*/  ddc; int /*<<< orphan*/  edid; scalar_t__ panel; } ;
struct imx_ldb {struct imx_ldb_channel* channel; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct imx_ldb* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  drm_panel_detach (scalar_t__) ; 
 int /*<<< orphan*/  i2c_put_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void imx_ldb_unbind(struct device *dev, struct device *master,
	void *data)
{
	struct imx_ldb *imx_ldb = dev_get_drvdata(dev);
	int i;

	for (i = 0; i < 2; i++) {
		struct imx_ldb_channel *channel = &imx_ldb->channel[i];

		if (channel->panel)
			drm_panel_detach(channel->panel);

		kfree(channel->edid);
		i2c_put_adapter(channel->ddc);
	}
}