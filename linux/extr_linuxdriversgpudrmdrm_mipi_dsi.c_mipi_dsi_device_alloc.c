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
struct mipi_dsi_host {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * type; int /*<<< orphan*/  parent; int /*<<< orphan*/ * bus; } ;
struct mipi_dsi_device {TYPE_1__ dev; struct mipi_dsi_host* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct mipi_dsi_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 struct mipi_dsi_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mipi_dsi_bus_type ; 
 int /*<<< orphan*/  mipi_dsi_device_type ; 

__attribute__((used)) static struct mipi_dsi_device *mipi_dsi_device_alloc(struct mipi_dsi_host *host)
{
	struct mipi_dsi_device *dsi;

	dsi = kzalloc(sizeof(*dsi), GFP_KERNEL);
	if (!dsi)
		return ERR_PTR(-ENOMEM);

	dsi->host = host;
	dsi->dev.bus = &mipi_dsi_bus_type;
	dsi->dev.parent = host->dev;
	dsi->dev.type = &mipi_dsi_device_type;

	device_initialize(&dsi->dev);

	return dsi;
}