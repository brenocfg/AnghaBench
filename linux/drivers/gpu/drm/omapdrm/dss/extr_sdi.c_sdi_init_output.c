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
struct omap_dss_device {char* name; int bus_flags; int /*<<< orphan*/  owner; int /*<<< orphan*/ * ops; int /*<<< orphan*/  of_ports; int /*<<< orphan*/  dispc_channel; int /*<<< orphan*/  type; int /*<<< orphan*/  id; int /*<<< orphan*/ * dev; } ;
struct sdi_device {TYPE_1__* pdev; struct omap_dss_device output; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int DRM_BUS_FLAG_PIXDATA_DRIVE_POSEDGE ; 
 int DRM_BUS_FLAG_SYNC_DRIVE_POSEDGE ; 
 int /*<<< orphan*/  OMAP_DISPLAY_TYPE_SDI ; 
 int /*<<< orphan*/  OMAP_DSS_CHANNEL_LCD ; 
 int /*<<< orphan*/  OMAP_DSS_OUTPUT_SDI ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int omapdss_device_init_output (struct omap_dss_device*) ; 
 int /*<<< orphan*/  omapdss_device_register (struct omap_dss_device*) ; 
 int /*<<< orphan*/  sdi_ops ; 

__attribute__((used)) static int sdi_init_output(struct sdi_device *sdi)
{
	struct omap_dss_device *out = &sdi->output;
	int r;

	out->dev = &sdi->pdev->dev;
	out->id = OMAP_DSS_OUTPUT_SDI;
	out->type = OMAP_DISPLAY_TYPE_SDI;
	out->name = "sdi.0";
	out->dispc_channel = OMAP_DSS_CHANNEL_LCD;
	/* We have SDI only on OMAP3, where it's on port 1 */
	out->of_ports = BIT(1);
	out->ops = &sdi_ops;
	out->owner = THIS_MODULE;
	out->bus_flags = DRM_BUS_FLAG_PIXDATA_DRIVE_POSEDGE	/* 15.5.9.1.2 */
		       | DRM_BUS_FLAG_SYNC_DRIVE_POSEDGE;

	r = omapdss_device_init_output(out);
	if (r < 0)
		return r;

	omapdss_device_register(out);

	return 0;
}