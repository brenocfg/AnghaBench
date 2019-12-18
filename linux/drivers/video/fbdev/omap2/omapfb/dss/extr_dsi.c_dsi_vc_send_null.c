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
struct omap_dss_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPI_DSI_NULL_PACKET ; 
 struct platform_device* dsi_get_dsidev_from_dssdev (struct omap_dss_device*) ; 
 int dsi_vc_send_long (struct platform_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsi_vc_send_null(struct omap_dss_device *dssdev, int channel)
{
	struct platform_device *dsidev = dsi_get_dsidev_from_dssdev(dssdev);

	return dsi_vc_send_long(dsidev, channel, MIPI_DSI_NULL_PACKET, NULL,
		0, 0);
}