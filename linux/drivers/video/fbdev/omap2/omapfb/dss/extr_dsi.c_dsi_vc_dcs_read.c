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
struct platform_device {int dummy; } ;
struct omap_dss_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSS_DSI_CONTENT_DCS ; 
 int EIO ; 
 struct platform_device* dsi_get_dsidev_from_dssdev (struct omap_dss_device*) ; 
 int dsi_vc_dcs_send_read_request (struct platform_device*,int,int /*<<< orphan*/ ) ; 
 int dsi_vc_read_rx_fifo (struct platform_device*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int dsi_vc_send_bta_sync (struct omap_dss_device*,int) ; 

__attribute__((used)) static int dsi_vc_dcs_read(struct omap_dss_device *dssdev, int channel, u8 dcs_cmd,
		u8 *buf, int buflen)
{
	struct platform_device *dsidev = dsi_get_dsidev_from_dssdev(dssdev);
	int r;

	r = dsi_vc_dcs_send_read_request(dsidev, channel, dcs_cmd);
	if (r)
		goto err;

	r = dsi_vc_send_bta_sync(dssdev, channel);
	if (r)
		goto err;

	r = dsi_vc_read_rx_fifo(dsidev, channel, buf, buflen,
		DSS_DSI_CONTENT_DCS);
	if (r < 0)
		goto err;

	if (r != buflen) {
		r = -EIO;
		goto err;
	}

	return 0;
err:
	DSSERR("dsi_vc_dcs_read(ch %d, cmd 0x%02x) failed\n", channel, dcs_cmd);
	return r;
}