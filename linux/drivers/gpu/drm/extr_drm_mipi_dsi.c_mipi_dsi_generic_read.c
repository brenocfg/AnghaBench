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
struct mipi_dsi_msg {size_t tx_len; void const* tx_buf; size_t rx_len; void* rx_buf; int /*<<< orphan*/  type; int /*<<< orphan*/  channel; } ;
struct mipi_dsi_device {int /*<<< orphan*/  channel; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  MIPI_DSI_GENERIC_READ_REQUEST_0_PARAM ; 
 int /*<<< orphan*/  MIPI_DSI_GENERIC_READ_REQUEST_1_PARAM ; 
 int /*<<< orphan*/  MIPI_DSI_GENERIC_READ_REQUEST_2_PARAM ; 
 int /*<<< orphan*/  mipi_dsi_device_transfer (struct mipi_dsi_device*,struct mipi_dsi_msg*) ; 

ssize_t mipi_dsi_generic_read(struct mipi_dsi_device *dsi, const void *params,
			      size_t num_params, void *data, size_t size)
{
	struct mipi_dsi_msg msg = {
		.channel = dsi->channel,
		.tx_len = num_params,
		.tx_buf = params,
		.rx_len = size,
		.rx_buf = data
	};

	switch (num_params) {
	case 0:
		msg.type = MIPI_DSI_GENERIC_READ_REQUEST_0_PARAM;
		break;

	case 1:
		msg.type = MIPI_DSI_GENERIC_READ_REQUEST_1_PARAM;
		break;

	case 2:
		msg.type = MIPI_DSI_GENERIC_READ_REQUEST_2_PARAM;
		break;

	default:
		return -EINVAL;
	}

	return mipi_dsi_device_transfer(dsi, &msg);
}