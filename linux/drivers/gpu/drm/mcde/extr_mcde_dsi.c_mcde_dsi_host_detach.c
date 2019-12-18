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
struct mipi_dsi_host {int dummy; } ;
struct mipi_dsi_device {int dummy; } ;
struct mcde_dsi {TYPE_1__* mcde; int /*<<< orphan*/ * mdsi; } ;
struct TYPE_2__ {int /*<<< orphan*/ * mdsi; } ;

/* Variables and functions */
 struct mcde_dsi* host_to_mcde_dsi (struct mipi_dsi_host*) ; 

__attribute__((used)) static int mcde_dsi_host_detach(struct mipi_dsi_host *host,
				struct mipi_dsi_device *mdsi)
{
	struct mcde_dsi *d = host_to_mcde_dsi(host);

	d->mdsi = NULL;
	if (d->mcde)
		d->mcde->mdsi = NULL;

	return 0;
}