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
struct mipi_dsi_host {int dummy; } ;
struct mipi_dsi_device {int dummy; } ;
struct cdns_dsi_output {int /*<<< orphan*/  bridge; scalar_t__ panel; } ;
struct cdns_dsi_input {int /*<<< orphan*/  bridge; } ;
struct cdns_dsi {struct cdns_dsi_input input; struct cdns_dsi_output output; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_bridge_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_panel_bridge_remove (int /*<<< orphan*/ ) ; 
 struct cdns_dsi* to_cdns_dsi (struct mipi_dsi_host*) ; 

__attribute__((used)) static int cdns_dsi_detach(struct mipi_dsi_host *host,
			   struct mipi_dsi_device *dev)
{
	struct cdns_dsi *dsi = to_cdns_dsi(host);
	struct cdns_dsi_output *output = &dsi->output;
	struct cdns_dsi_input *input = &dsi->input;

	drm_bridge_remove(&input->bridge);
	if (output->panel)
		drm_panel_bridge_remove(output->bridge);

	return 0;
}