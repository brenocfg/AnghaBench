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
struct mipi_dsi_msg {int /*<<< orphan*/  flags; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  rx_len; } ;
struct mipi_dsi_host {int dummy; } ;
struct exynos_dsi_transfer {int rx_done; int /*<<< orphan*/  flags; int /*<<< orphan*/  rx_payload; int /*<<< orphan*/  rx_len; int /*<<< orphan*/  packet; } ;
struct exynos_dsi {int state; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int DSIM_STATE_ENABLED ; 
 int DSIM_STATE_INITIALIZED ; 
 int EINVAL ; 
 int exynos_dsi_init (struct exynos_dsi*) ; 
 int exynos_dsi_transfer (struct exynos_dsi*,struct exynos_dsi_transfer*) ; 
 struct exynos_dsi* host_to_dsi (struct mipi_dsi_host*) ; 
 int mipi_dsi_create_packet (int /*<<< orphan*/ *,struct mipi_dsi_msg const*) ; 

__attribute__((used)) static ssize_t exynos_dsi_host_transfer(struct mipi_dsi_host *host,
					 const struct mipi_dsi_msg *msg)
{
	struct exynos_dsi *dsi = host_to_dsi(host);
	struct exynos_dsi_transfer xfer;
	int ret;

	if (!(dsi->state & DSIM_STATE_ENABLED))
		return -EINVAL;

	if (!(dsi->state & DSIM_STATE_INITIALIZED)) {
		ret = exynos_dsi_init(dsi);
		if (ret)
			return ret;
		dsi->state |= DSIM_STATE_INITIALIZED;
	}

	ret = mipi_dsi_create_packet(&xfer.packet, msg);
	if (ret < 0)
		return ret;

	xfer.rx_len = msg->rx_len;
	xfer.rx_payload = msg->rx_buf;
	xfer.flags = msg->flags;

	ret = exynos_dsi_transfer(dsi, &xfer);
	return (ret < 0) ? ret : xfer.rx_done;
}