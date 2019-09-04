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
struct mipi_dsi_msg {int tx_len; void* rx_buf; size_t rx_len; int /*<<< orphan*/ * tx_buf; int /*<<< orphan*/  type; int /*<<< orphan*/  channel; } ;
struct mipi_dsi_device {int /*<<< orphan*/  channel; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  MIPI_DSI_DCS_READ ; 
 int /*<<< orphan*/  mipi_dsi_device_transfer (struct mipi_dsi_device*,struct mipi_dsi_msg*) ; 

ssize_t mipi_dsi_dcs_read(struct mipi_dsi_device *dsi, u8 cmd, void *data,
			  size_t len)
{
	struct mipi_dsi_msg msg = {
		.channel = dsi->channel,
		.type = MIPI_DSI_DCS_READ,
		.tx_buf = &cmd,
		.tx_len = 1,
		.rx_buf = data,
		.rx_len = len
	};

	return mipi_dsi_device_transfer(dsi, &msg);
}