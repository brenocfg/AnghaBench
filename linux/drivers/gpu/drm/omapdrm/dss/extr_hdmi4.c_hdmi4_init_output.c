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
struct omap_dss_device {char* name; int /*<<< orphan*/  ops_flags; int /*<<< orphan*/  of_ports; int /*<<< orphan*/  owner; int /*<<< orphan*/ * ops; int /*<<< orphan*/  dispc_channel; int /*<<< orphan*/  type; int /*<<< orphan*/  id; int /*<<< orphan*/ * dev; } ;
struct omap_hdmi {TYPE_1__* pdev; struct omap_dss_device output; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OMAP_DISPLAY_TYPE_HDMI ; 
 int /*<<< orphan*/  OMAP_DSS_CHANNEL_DIGIT ; 
 int /*<<< orphan*/  OMAP_DSS_DEVICE_OP_EDID ; 
 int /*<<< orphan*/  OMAP_DSS_OUTPUT_HDMI ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  hdmi_ops ; 
 int omapdss_device_init_output (struct omap_dss_device*) ; 
 int /*<<< orphan*/  omapdss_device_register (struct omap_dss_device*) ; 

__attribute__((used)) static int hdmi4_init_output(struct omap_hdmi *hdmi)
{
	struct omap_dss_device *out = &hdmi->output;
	int r;

	out->dev = &hdmi->pdev->dev;
	out->id = OMAP_DSS_OUTPUT_HDMI;
	out->type = OMAP_DISPLAY_TYPE_HDMI;
	out->name = "hdmi.0";
	out->dispc_channel = OMAP_DSS_CHANNEL_DIGIT;
	out->ops = &hdmi_ops;
	out->owner = THIS_MODULE;
	out->of_ports = BIT(0);
	out->ops_flags = OMAP_DSS_DEVICE_OP_EDID;

	r = omapdss_device_init_output(out);
	if (r < 0)
		return r;

	omapdss_device_register(out);

	return 0;
}