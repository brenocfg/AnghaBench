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
typedef  int /*<<< orphan*/  u8 ;
struct omap_dss_device {int dummy; } ;
struct dsi_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSS_DSI_CONTENT_DCS ; 
 int dsi_vc_write_nosync_common (struct dsi_data*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct dsi_data* to_dsi_data (struct omap_dss_device*) ; 

__attribute__((used)) static int dsi_vc_dcs_write_nosync(struct omap_dss_device *dssdev, int channel,
		u8 *data, int len)
{
	struct dsi_data *dsi = to_dsi_data(dssdev);

	return dsi_vc_write_nosync_common(dsi, channel, data, len,
			DSS_DSI_CONTENT_DCS);
}