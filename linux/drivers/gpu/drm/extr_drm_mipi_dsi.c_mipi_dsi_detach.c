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
struct mipi_dsi_host_ops {int (* detach ) (TYPE_1__*,struct mipi_dsi_device*) ;} ;
struct mipi_dsi_device {TYPE_1__* host; } ;
struct TYPE_2__ {struct mipi_dsi_host_ops* ops; } ;

/* Variables and functions */
 int ENOSYS ; 
 int stub1 (TYPE_1__*,struct mipi_dsi_device*) ; 

int mipi_dsi_detach(struct mipi_dsi_device *dsi)
{
	const struct mipi_dsi_host_ops *ops = dsi->host->ops;

	if (!ops || !ops->detach)
		return -ENOSYS;

	return ops->detach(dsi->host, dsi);
}