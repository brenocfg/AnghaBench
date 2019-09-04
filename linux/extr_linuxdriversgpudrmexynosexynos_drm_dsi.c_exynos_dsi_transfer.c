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
struct mipi_dsi_packet {int /*<<< orphan*/  payload; scalar_t__ payload_length; int /*<<< orphan*/  header; } ;
struct exynos_dsi_transfer {int result; struct mipi_dsi_packet packet; int /*<<< orphan*/  completed; int /*<<< orphan*/  list; scalar_t__ rx_done; scalar_t__ tx_done; } ;
struct exynos_dsi {int /*<<< orphan*/  dev; int /*<<< orphan*/  transfer_lock; int /*<<< orphan*/  transfer_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_XFER_TIMEOUT_MS ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_dsi_remove_transfer (struct exynos_dsi*,struct exynos_dsi_transfer*) ; 
 int /*<<< orphan*/  exynos_dsi_transfer_start (struct exynos_dsi*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int exynos_dsi_transfer(struct exynos_dsi *dsi,
					struct exynos_dsi_transfer *xfer)
{
	unsigned long flags;
	bool stopped;

	xfer->tx_done = 0;
	xfer->rx_done = 0;
	xfer->result = -ETIMEDOUT;
	init_completion(&xfer->completed);

	spin_lock_irqsave(&dsi->transfer_lock, flags);

	stopped = list_empty(&dsi->transfer_list);
	list_add_tail(&xfer->list, &dsi->transfer_list);

	spin_unlock_irqrestore(&dsi->transfer_lock, flags);

	if (stopped)
		exynos_dsi_transfer_start(dsi);

	wait_for_completion_timeout(&xfer->completed,
				    msecs_to_jiffies(DSI_XFER_TIMEOUT_MS));
	if (xfer->result == -ETIMEDOUT) {
		struct mipi_dsi_packet *pkt = &xfer->packet;
		exynos_dsi_remove_transfer(dsi, xfer);
		dev_err(dsi->dev, "xfer timed out: %*ph %*ph\n", 4, pkt->header,
			(int)pkt->payload_length, pkt->payload);
		return -ETIMEDOUT;
	}

	/* Also covers hardware timeout condition */
	return xfer->result;
}