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
struct omap_hdmi {TYPE_1__* dss; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dispc; } ;

/* Variables and functions */
 struct omap_hdmi* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dispc_runtime_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdmi_runtime_suspend(struct device *dev)
{
	struct omap_hdmi *hdmi = dev_get_drvdata(dev);

	dispc_runtime_put(hdmi->dss->dispc);

	return 0;
}