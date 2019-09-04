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
struct mipi_dsi_host {int /*<<< orphan*/  dev; } ;
struct mipi_dsi_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  channel; struct mipi_dsi_host* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int device_add (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mipi_dsi_device_add(struct mipi_dsi_device *dsi)
{
	struct mipi_dsi_host *host = dsi->host;

	dev_set_name(&dsi->dev, "%s.%d", dev_name(host->dev),  dsi->channel);

	return device_add(&dsi->dev);
}