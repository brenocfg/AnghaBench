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
struct TYPE_2__ {scalar_t__ stream_count; } ;
struct dc_link {TYPE_1__ mst_stream_alloc_table; } ;
typedef  enum signal_type { ____Placeholder_signal_type } signal_type ;

/* Variables and functions */
 int /*<<< orphan*/  dp_disable_link_phy (struct dc_link*,int) ; 
 int /*<<< orphan*/  dp_enable_mst_on_sink (struct dc_link*,int) ; 

void dp_disable_link_phy_mst(struct dc_link *link, enum signal_type signal)
{
	/* MST disable link only when no stream use the link */
	if (link->mst_stream_alloc_table.stream_count > 0)
		return;

	dp_disable_link_phy(link, signal);

	/* set the sink to SST mode after disabling the link */
	dp_enable_mst_on_sink(link, false);
}