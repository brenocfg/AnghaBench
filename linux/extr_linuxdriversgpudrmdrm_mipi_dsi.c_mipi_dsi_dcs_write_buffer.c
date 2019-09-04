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
struct mipi_dsi_msg {void const* tx_buf; size_t tx_len; int /*<<< orphan*/  type; int /*<<< orphan*/  channel; } ;
struct mipi_dsi_device {int /*<<< orphan*/  channel; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  MIPI_DSI_DCS_LONG_WRITE ; 
 int /*<<< orphan*/  MIPI_DSI_DCS_SHORT_WRITE ; 
 int /*<<< orphan*/  MIPI_DSI_DCS_SHORT_WRITE_PARAM ; 
 int /*<<< orphan*/  mipi_dsi_device_transfer (struct mipi_dsi_device*,struct mipi_dsi_msg*) ; 

ssize_t mipi_dsi_dcs_write_buffer(struct mipi_dsi_device *dsi,
				  const void *data, size_t len)
{
	struct mipi_dsi_msg msg = {
		.channel = dsi->channel,
		.tx_buf = data,
		.tx_len = len
	};

	switch (len) {
	case 0:
		return -EINVAL;

	case 1:
		msg.type = MIPI_DSI_DCS_SHORT_WRITE;
		break;

	case 2:
		msg.type = MIPI_DSI_DCS_SHORT_WRITE_PARAM;
		break;

	default:
		msg.type = MIPI_DSI_DCS_LONG_WRITE;
		break;
	}

	return mipi_dsi_device_transfer(dsi, &msg);
}