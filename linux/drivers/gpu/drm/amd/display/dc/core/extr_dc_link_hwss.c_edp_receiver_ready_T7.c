#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dc_link {TYPE_3__* local_sink; } ;
typedef  int /*<<< orphan*/  sinkstatus ;
typedef  enum dc_status { ____Placeholder_dc_status } dc_status ;
typedef  int /*<<< orphan*/  edpRev ;
struct TYPE_4__ {int extra_t7_ms; } ;
struct TYPE_5__ {TYPE_1__ panel_patch; } ;
struct TYPE_6__ {TYPE_2__ edid_caps; } ;

/* Variables and functions */
 int DC_OK ; 
 unsigned char DP_EDP_12 ; 
 int /*<<< orphan*/  DP_EDP_DPCD_REV ; 
 int /*<<< orphan*/  DP_SINK_STATUS ; 
 int core_link_read_dpcd (struct dc_link*,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

bool edp_receiver_ready_T7(struct dc_link *link)
{
	unsigned int tries = 0;
	unsigned char sinkstatus = 0;
	unsigned char edpRev = 0;
	enum dc_status result = DC_OK;

	result = core_link_read_dpcd(link, DP_EDP_DPCD_REV, &edpRev, sizeof(edpRev));
	if (result == DC_OK && edpRev < DP_EDP_12)
		return true;
	/* start from eDP version 1.2, SINK_STAUS indicate the sink is ready.*/
	do {
		sinkstatus = 0;
		result = core_link_read_dpcd(link, DP_SINK_STATUS, &sinkstatus, sizeof(sinkstatus));
		if (sinkstatus == 1)
			break;
		if (result != DC_OK)
			break;
		udelay(25); //MAx T7 is 50ms
	} while (++tries < 300);

	if (link->local_sink->edid_caps.panel_patch.extra_t7_ms > 0)
		udelay(link->local_sink->edid_caps.panel_patch.extra_t7_ms * 1000);

	return result;
}