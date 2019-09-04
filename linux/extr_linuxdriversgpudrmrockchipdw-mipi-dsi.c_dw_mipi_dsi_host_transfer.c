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
struct mipi_dsi_msg {int type; } ;
struct mipi_dsi_host {int dummy; } ;
struct dw_mipi_dsi {int /*<<< orphan*/  dev; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int EINVAL ; 
#define  MIPI_DSI_DCS_LONG_WRITE 131 
#define  MIPI_DSI_DCS_SHORT_WRITE 130 
#define  MIPI_DSI_DCS_SHORT_WRITE_PARAM 129 
#define  MIPI_DSI_SET_MAXIMUM_RETURN_PACKET_SIZE 128 
 int dw_mipi_dsi_dcs_long_write (struct dw_mipi_dsi*,struct mipi_dsi_msg const*) ; 
 int dw_mipi_dsi_dcs_short_write (struct dw_mipi_dsi*,struct mipi_dsi_msg const*) ; 
 int /*<<< orphan*/  dw_mipi_message_config (struct dw_mipi_dsi*,struct mipi_dsi_msg const*) ; 
 struct dw_mipi_dsi* host_to_dsi (struct mipi_dsi_host*) ; 

__attribute__((used)) static ssize_t dw_mipi_dsi_host_transfer(struct mipi_dsi_host *host,
					 const struct mipi_dsi_msg *msg)
{
	struct dw_mipi_dsi *dsi = host_to_dsi(host);
	int ret;

	dw_mipi_message_config(dsi, msg);

	switch (msg->type) {
	case MIPI_DSI_DCS_SHORT_WRITE:
	case MIPI_DSI_DCS_SHORT_WRITE_PARAM:
	case MIPI_DSI_SET_MAXIMUM_RETURN_PACKET_SIZE:
		ret = dw_mipi_dsi_dcs_short_write(dsi, msg);
		break;
	case MIPI_DSI_DCS_LONG_WRITE:
		ret = dw_mipi_dsi_dcs_long_write(dsi, msg);
		break;
	default:
		DRM_DEV_ERROR(dsi->dev, "unsupported message type 0x%02x\n",
			      msg->type);
		ret = -EINVAL;
	}

	return ret;
}