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
typedef  unsigned int u32 ;
typedef  enum omap_plane { ____Placeholder_omap_plane } omap_plane ;

/* Variables and functions */
 int /*<<< orphan*/  FEAT_OMAP3_DSI_FIFO_BUG ; 
 int OMAP_DSS_WB ; 
 unsigned int dispc_ovl_get_burst_size (int) ; 
 unsigned int dispc_ovl_get_fifo_size (int) ; 
 unsigned int dss_feat_get_buffer_size_unit () ; 
 int dss_feat_get_num_ovls () ; 
 scalar_t__ dss_has_feature (int /*<<< orphan*/ ) ; 

void dispc_ovl_compute_fifo_thresholds(enum omap_plane plane,
		u32 *fifo_low, u32 *fifo_high, bool use_fifomerge,
		bool manual_update)
{
	/*
	 * All sizes are in bytes. Both the buffer and burst are made of
	 * buffer_units, and the fifo thresholds must be buffer_unit aligned.
	 */

	unsigned buf_unit = dss_feat_get_buffer_size_unit();
	unsigned ovl_fifo_size, total_fifo_size, burst_size;
	int i;

	burst_size = dispc_ovl_get_burst_size(plane);
	ovl_fifo_size = dispc_ovl_get_fifo_size(plane);

	if (use_fifomerge) {
		total_fifo_size = 0;
		for (i = 0; i < dss_feat_get_num_ovls(); ++i)
			total_fifo_size += dispc_ovl_get_fifo_size(i);
	} else {
		total_fifo_size = ovl_fifo_size;
	}

	/*
	 * We use the same low threshold for both fifomerge and non-fifomerge
	 * cases, but for fifomerge we calculate the high threshold using the
	 * combined fifo size
	 */

	if (manual_update && dss_has_feature(FEAT_OMAP3_DSI_FIFO_BUG)) {
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