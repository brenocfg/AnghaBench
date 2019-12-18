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
typedef  int u16 ;
struct omap_dss_device {int dummy; } ;
struct TYPE_2__ {int hactive; int vactive; } ;
struct dsi_data {int update_channel; void (* framedone_callback ) (int,void*) ;int update_bytes; int /*<<< orphan*/  pix_fmt; TYPE_1__ vm; void* framedone_data; } ;

/* Variables and functions */
 int dsi_get_pixel_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_perf_mark_setup (struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_update_screen_dispc (struct dsi_data*) ; 
 struct dsi_data* to_dsi_data (struct omap_dss_device*) ; 

__attribute__((used)) static int dsi_update(struct omap_dss_device *dssdev, int channel,
		void (*callback)(int, void *), void *data)
{
	struct dsi_data *dsi = to_dsi_data(dssdev);
	u16 dw, dh;

	dsi_perf_mark_setup(dsi);

	dsi->update_channel = channel;

	dsi->framedone_callback = callback;
	dsi->framedone_data = data;

	dw = dsi->vm.hactive;
	dh = dsi->vm.vactive;

#ifdef DSI_PERF_MEASURE
	dsi->update_bytes = dw * dh *
		dsi_get_pixel_size(dsi->pix_fmt) / 8;
#endif
	dsi_update_screen_dispc(dsi);

	return 0;
}