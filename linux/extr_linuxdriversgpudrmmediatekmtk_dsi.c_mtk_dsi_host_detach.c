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
struct TYPE_2__ {scalar_t__ dev; } ;
struct mtk_dsi {TYPE_1__ conn; } ;
struct mipi_dsi_host {int dummy; } ;
struct mipi_dsi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_helper_hpd_irq_event (scalar_t__) ; 
 struct mtk_dsi* host_to_dsi (struct mipi_dsi_host*) ; 

__attribute__((used)) static int mtk_dsi_host_detach(struct mipi_dsi_host *host,
			       struct mipi_dsi_device *device)
{
	struct mtk_dsi *dsi = host_to_dsi(host);

	if (dsi->conn.dev)
		drm_helper_hpd_irq_event(dsi->conn.dev);

	return 0;
}