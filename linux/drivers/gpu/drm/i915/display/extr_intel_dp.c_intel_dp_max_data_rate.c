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

/* Variables and functions */

int
intel_dp_max_data_rate(int max_link_clock, int max_lanes)
{
	/* max_link_clock is the link symbol clock (LS_Clk) in kHz and not the
	 * link rate that is generally expressed in Gbps. Since, 8 bits of data
	 * is transmitted every LS_Clk per lane, there is no need to account for
	 * the channel encoding that is done in the PHY layer here.
	 */

	return max_link_clock * max_lanes;
}