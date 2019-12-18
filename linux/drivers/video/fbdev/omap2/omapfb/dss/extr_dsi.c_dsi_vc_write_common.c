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
typedef  enum dss_dsi_content_type { ____Placeholder_dss_dsi_content_type } dss_dsi_content_type ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_VC_CTRL (int) ; 
 int /*<<< orphan*/  DSSERR (char*,...) ; 
 int EIO ; 
 scalar_t__ REG_GET (struct platform_device*,int /*<<< orphan*/ ,int,int) ; 
 struct platform_device* dsi_get_dsidev_from_dssdev (struct omap_dss_device*) ; 
 int /*<<< orphan*/  dsi_vc_flush_receive_data (struct platform_device*,int) ; 
 int dsi_vc_send_bta_sync (struct omap_dss_device*,int) ; 
 int dsi_vc_write_nosync_common (struct platform_device*,int,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int dsi_vc_write_common(struct omap_dss_device *dssdev, int channel,
		u8 *data, int len, enum dss_dsi_content_type type)
{
	struct platform_device *dsidev = dsi_get_dsidev_from_dssdev(dssdev);
	int r;

	r = dsi_vc_write_nosync_common(dsidev, channel, data, len, type);
	if (r)
		goto err;

	r = dsi_vc_send_bta_sync(dssdev, channel);
	if (r)
		goto err;

	/* RX_FIFO_NOT_EMPTY */
	if (REG_GET(dsidev, DSI_VC_CTRL(channel), 20, 20)) {
		DSSERR("rx fifo not empty after write, dumping data:\n");
		dsi_vc_flush_receive_data(dsidev, channel);
		r = -EIO;
		goto err;
	}

	return 0;
err:
	DSSERR("dsi_vc_write_common(ch %d, cmd 0x%02x, len %d) failed\n",
			channel, data[0], len);
	return r;
}