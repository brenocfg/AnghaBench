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
typedef  unsigned int u32 ;
struct dispc_device {TYPE_1__* feat; } ;
typedef  enum omap_plane_id { ____Placeholder_omap_plane_id } omap_plane_id ;
struct TYPE_2__ {unsigned int buffer_size_unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  FEAT_OMAP3_DSI_FIFO_BUG ; 
 int OMAP_DSS_WB ; 
 int dispc_get_num_ovls (struct dispc_device*) ; 
 scalar_t__ dispc_has_feature (struct dispc_device*,int /*<<< orphan*/ ) ; 
 unsigned int dispc_ovl_get_burst_size (struct dispc_device*,int) ; 
 unsigned int dispc_ovl_get_fifo_size (struct dispc_device*,int) ; 

void dispc_ovl_compute_fifo_thresholds(struct dispc_device *dispc,
				       enum omap_plane_id plane,
				       u32 *fifo_low, u32 *fifo_high,
				       bool use_fifomerge, bool manual_update)
{
	/*
	 * All sizes are in bytes. Both the buffer and burst are made of
	 * buffer_units, and the fifo thresholds must be buffer_unit aligned.
	 */
	unsigned int buf_unit = dispc->feat->buffer_size_unit;
	unsigned int ovl_fifo_size, total_fifo_size, burst_size;
	int i;

	burst_size = dispc_ovl_get_burst_size(dispc, plane);
	ovl_fifo_size = dispc_ovl_get_fifo_size(dispc, plane);

	if (use_fifomerge) {
		total_fifo_size = 0;
		for (i = 0; i < dispc_get_num_ovls(dispc); ++i)
			total_fifo_size += dispc_ovl_get_fifo_size(dispc, i);
	} else {
		total_fifo_size = ovl_fifo_size;
	}

	/*
	 * We use the same low threshold for both fifomerge and non-fifomerge
	 * cases, but for fifomerge we calculate the high threshold using the
	 * combined fifo size
	 */

	if (manual_update && dispc_has_feature(dispc, FEAT_OMAP3_DSI_FIFO_BUG)) {
		*fifo_low = ovl_fifo_size - burst_size * 2;
		*fifo_high = total_fifo_size - burst_size;
	} else if (plane == OMAP_DSS_WB) {
		/*
		 * Most optimal configuration for writeback is to push out data
		 * to the interconnect the moment writeback pushes enough pixels
		 * in the FIFO to form a burst
		 */
		*fifo_low = 0;
		*fifo_high = burst_size;
	} else {
		*fifo_low = ovl_fifo_size - burst_size;
		*fifo_high = total_fifo_size - buf_unit;
	}
}