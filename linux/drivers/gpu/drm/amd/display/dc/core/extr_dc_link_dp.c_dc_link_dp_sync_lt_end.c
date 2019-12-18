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
struct dc_link {int sync_lt_in_progress; int /*<<< orphan*/  connector_signal; } ;

/* Variables and functions */
 int /*<<< orphan*/  dp_disable_link_phy (struct dc_link*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dp_set_fec_ready (struct dc_link*,int) ; 

bool dc_link_dp_sync_lt_end(struct dc_link *link, bool link_down)
{
	/* If input parameter is set, shut down phy.
	 * Still shouldn't turn off dp_receiver (DPCD:600h)
	 */
	if (link_down == true) {
		dp_disable_link_phy(link, link->connector_signal);
#ifdef CONFIG_DRM_AMD_DC_DSC_SUPPORT
		dp_set_fec_ready(link, false);
#endif
	}

	link->sync_lt_in_progress = false;
	return true;
}