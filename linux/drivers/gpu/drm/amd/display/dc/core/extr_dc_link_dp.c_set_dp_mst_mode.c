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
struct dc_link {scalar_t__ type; TYPE_1__* local_sink; int /*<<< orphan*/  connector_signal; TYPE_1__** remote_sinks; } ;
struct TYPE_2__ {int /*<<< orphan*/  sink_signal; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGNAL_TYPE_DISPLAY_PORT ; 
 int /*<<< orphan*/  SIGNAL_TYPE_DISPLAY_PORT_MST ; 
 scalar_t__ dc_connection_mst_branch ; 
 scalar_t__ dc_connection_single ; 
 int /*<<< orphan*/  dp_disable_link_phy (struct dc_link*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dp_disable_link_phy_mst (struct dc_link*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dp_enable_mst_on_sink (struct dc_link*,int) ; 

__attribute__((used)) static void set_dp_mst_mode(struct dc_link *link, bool mst_enable)
{
	if (mst_enable == false &&
		link->type == dc_connection_mst_branch) {
		/* Disable MST on link. Use only local sink. */
		dp_disable_link_phy_mst(link, link->connector_signal);

		link->type = dc_connection_single;
		link->local_sink = link->remote_sinks[0];
		link->local_sink->sink_signal = SIGNAL_TYPE_DISPLAY_PORT;
	} else if (mst_enable == true &&
			link->type == dc_connection_single &&
			link->remote_sinks[0] != NULL) {
		/* Re-enable MST on link. */
		dp_disable_link_phy(link, link->connector_signal);
		dp_enable_mst_on_sink(link, true);

		link->type = dc_connection_mst_branch;
		link->local_sink->sink_signal = SIGNAL_TYPE_DISPLAY_PORT_MST;
	}
}