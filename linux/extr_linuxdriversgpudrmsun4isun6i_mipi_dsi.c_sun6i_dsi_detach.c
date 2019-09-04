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
struct sun6i_dsi {int /*<<< orphan*/ * device; int /*<<< orphan*/ * panel; } ;
struct mipi_dsi_host {int dummy; } ;
struct mipi_dsi_device {int dummy; } ;

/* Variables and functions */
 struct sun6i_dsi* host_to_sun6i_dsi (struct mipi_dsi_host*) ; 

__attribute__((used)) static int sun6i_dsi_detach(struct mipi_dsi_host *host,
			    struct mipi_dsi_device *device)
{
	struct sun6i_dsi *dsi = host_to_sun6i_dsi(host);

	dsi->panel = NULL;
	dsi->device = NULL;

	return 0;
}