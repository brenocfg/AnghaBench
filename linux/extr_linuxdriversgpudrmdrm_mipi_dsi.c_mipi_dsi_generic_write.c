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
 int /*<<< orphan*/  MIPI_DSI_GENERIC_LONG_WRITE ; 
 int /*<<< orphan*/  MIPI_DSI_GENERIC_SHORT_WRITE_0_PARAM ; 
 int /*<<< orphan*/  MIPI_DSI_GENERIC_SHORT_WRITE_1_PARAM ; 
 int /*<<< orphan*/  MIPI_DSI_GENERIC_SHORT_WRITE_2_PARAM ; 
 int /*<<< orphan*/  mipi_dsi_device_transfer (struct mipi_dsi_device*,struct mipi_dsi_msg*) ; 

ssize_t mipi_dsi_generic_write(struct mipi_dsi_device *dsi, const void *payload,
			       size_t size)
{
	struct mipi_dsi_msg msg = {
		.channel = dsi->channel,
		.tx_buf = payload,
		.tx_len = size
	};

	switch (size) {
	case 0:
		msg.type = MIPI_DSI_GENERIC_SHORT_WRITE_0_PARAM;
		break;

	case 1:
		msg.type = MIPI_DSI_GENERIC_SHORT_WRITE_1_PARAM;
		break;

	case 2:
		msg.type = MIPI_DSI_GENERIC_SHORT_WRITE_2_PARAM;
		break;

	default:
		msg.type = MIPI_DSI_GENERIC_LONG_WRITE;
		break;
	}

	return mipi_dsi_device_transfer(dsi, &msg);
}