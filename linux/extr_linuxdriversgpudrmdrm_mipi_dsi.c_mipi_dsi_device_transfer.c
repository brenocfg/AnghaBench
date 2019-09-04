#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mipi_dsi_msg {int /*<<< orphan*/  flags; } ;
struct mipi_dsi_host_ops {int /*<<< orphan*/  (* transfer ) (TYPE_1__*,struct mipi_dsi_msg*) ;} ;
struct mipi_dsi_device {int mode_flags; TYPE_1__* host; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {struct mipi_dsi_host_ops* ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 int MIPI_DSI_MODE_LPM ; 
 int /*<<< orphan*/  MIPI_DSI_MSG_USE_LPM ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,struct mipi_dsi_msg*) ; 

__attribute__((used)) static ssize_t mipi_dsi_device_transfer(struct mipi_dsi_device *dsi,
					struct mipi_dsi_msg *msg)
{
	const struct mipi_dsi_host_ops *ops = dsi->host->ops;

	if (!ops || !ops->transfer)
		return -ENOSYS;

	if (dsi->mode_flags & MIPI_DSI_MODE_LPM)
		msg->flags |= MIPI_DSI_MSG_USE_LPM;

	return ops->transfer(dsi->host, msg);
}