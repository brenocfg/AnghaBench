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
struct mipi_dsi_packet {int size; } ;
struct mipi_dsi_msg {int rx_len; scalar_t__ rx_buf; } ;
struct mipi_dsi_host {int dummy; } ;
struct dw_mipi_dsi {struct dw_mipi_dsi* slave; int /*<<< orphan*/  dev; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int dw_mipi_dsi_read (struct dw_mipi_dsi*,struct mipi_dsi_msg const*) ; 
 int dw_mipi_dsi_write (struct dw_mipi_dsi*,struct mipi_dsi_packet*) ; 
 int /*<<< orphan*/  dw_mipi_message_config (struct dw_mipi_dsi*,struct mipi_dsi_msg const*) ; 
 struct dw_mipi_dsi* host_to_dsi (struct mipi_dsi_host*) ; 
 int mipi_dsi_create_packet (struct mipi_dsi_packet*,struct mipi_dsi_msg const*) ; 

__attribute__((used)) static ssize_t dw_mipi_dsi_host_transfer(struct mipi_dsi_host *host,
					 const struct mipi_dsi_msg *msg)
{
	struct dw_mipi_dsi *dsi = host_to_dsi(host);
	struct mipi_dsi_packet packet;
	int ret, nb_bytes;

	ret = mipi_dsi_create_packet(&packet, msg);
	if (ret) {
		dev_err(dsi->dev, "failed to create packet: %d\n", ret);
		return ret;
	}

	dw_mipi_message_config(dsi, msg);
	if (dsi->slave)
		dw_mipi_message_config(dsi->slave, msg);

	ret = dw_mipi_dsi_write(dsi, &packet);
	if (ret)
		return ret;
	if (dsi->slave) {
		ret = dw_mipi_dsi_write(dsi->slave, &packet);
		if (ret)
			return ret;
	}

	if (msg->rx_buf && msg->rx_len) {
		ret = dw_mipi_dsi_read(dsi, msg);
		if (ret)
			return ret;
		nb_bytes = msg->rx_len;
	} else {
		nb_bytes = packet.size;
	}

	return nb_bytes;
}