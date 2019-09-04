#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dc_link {TYPE_2__* link_enc; } ;
typedef  enum signal_type { ____Placeholder_signal_type } signal_type ;
struct TYPE_4__ {TYPE_1__* funcs; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* disable_output ) (TYPE_2__*,int) ;} ;

/* Variables and functions */
 scalar_t__ dc_is_dp_signal (int) ; 
 scalar_t__ dc_is_dp_sst_signal (int) ; 
 int /*<<< orphan*/  dp_disable_link_phy (struct dc_link*,int) ; 
 int /*<<< orphan*/  dp_disable_link_phy_mst (struct dc_link*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int) ; 

__attribute__((used)) static void disable_link(struct dc_link *link, enum signal_type signal)
{
	/*
	 * TODO: implement call for dp_set_hw_test_pattern
	 * it is needed for compliance testing
	 */

	/* here we need to specify that encoder output settings
	 * need to be calculated as for the set mode,
	 * it will lead to querying dynamic link capabilities
	 * which should be done before enable output */

	if (dc_is_dp_signal(signal)) {
		/* SST DP, eDP */
		if (dc_is_dp_sst_signal(signal))
			dp_disable_link_phy(link, signal);
		else
			dp_disable_link_phy_mst(link, signal);
	} else
		link->link_enc->funcs->disable_output(link->link_enc, signal);
}