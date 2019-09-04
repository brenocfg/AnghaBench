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
struct omap_dss_device {int dummy; } ;
struct dsi_data {TYPE_1__* vc; } ;
struct TYPE_2__ {scalar_t__ vc_id; struct omap_dss_device* dssdev; } ;

/* Variables and functions */
 struct dsi_data* to_dsi_data (struct omap_dss_device*) ; 

__attribute__((used)) static void dsi_release_vc(struct omap_dss_device *dssdev, int channel)
{
	struct dsi_data *dsi = to_dsi_data(dssdev);

	if ((channel >= 0 && channel <= 3) &&
		dsi->vc[channel].dssdev == dssdev) {
		dsi->vc[channel].dssdev = NULL;
		dsi->vc[channel].vc_id = 0;
	}
}