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
union dp_downstream_port_present {void* byte; int /*<<< orphan*/  member_0; } ;
typedef  void* uint8_t ;
struct TYPE_6__ {int dp_keep_receiver_powered; } ;
struct TYPE_4__ {void* raw; } ;
struct TYPE_5__ {scalar_t__ dongle_type; int branch_dev_id; TYPE_1__ dpcd_rev; } ;
struct dc_link {TYPE_3__ wa_flags; TYPE_2__ dpcd_caps; } ;

/* Variables and functions */
 scalar_t__ DISPLAY_DONGLE_DP_VGA_CONVERTER ; 
#define  DP_BRANCH_DEVICE_ID_0010FA 129 
#define  DP_BRANCH_DEVICE_ID_0080E1 128 
 size_t DP_DOWNSTREAMPORT_PRESENT ; 
 size_t DP_DPCD_REV ; 
 int /*<<< orphan*/  core_link_read_dpcd (struct dc_link*,size_t,void**,int) ; 
 int /*<<< orphan*/  dp_receiver_power_ctrl (struct dc_link*,int) ; 

__attribute__((used)) static void dp_wa_power_up_0010FA(struct dc_link *link, uint8_t *dpcd_data,
		int length)
{
	int retry = 0;
	union dp_downstream_port_present ds_port = { 0 };

	if (!link->dpcd_caps.dpcd_rev.raw) {
		do {
			dp_receiver_power_ctrl(link, true);
			core_link_read_dpcd(link, DP_DPCD_REV,
							dpcd_data, length);
			link->dpcd_caps.dpcd_rev.raw = dpcd_data[
				DP_DPCD_REV -
				DP_DPCD_REV];
		} while (retry++ < 4 && !link->dpcd_caps.dpcd_rev.raw);
	}

	ds_port.byte = dpcd_data[DP_DOWNSTREAMPORT_PRESENT -
				 DP_DPCD_REV];

	if (link->dpcd_caps.dongle_type == DISPLAY_DONGLE_DP_VGA_CONVERTER) {
		switch (link->dpcd_caps.branch_dev_id) {
		/* 0010FA active dongles (DP-VGA, DP-DLDVI converters) power down
		 * all internal circuits including AUX communication preventing
		 * reading DPCD table and EDID (spec violation).
		 * Encoder will skip DP RX power down on disable_output to
		 * keep receiver powered all the time.*/
		case DP_BRANCH_DEVICE_ID_0010FA:
		case DP_BRANCH_DEVICE_ID_0080E1:
			link->wa_flags.dp_keep_receiver_powered = true;
			break;

		/* TODO: May need work around for other dongles. */
		default:
			link->wa_flags.dp_keep_receiver_powered = false;
			break;
		}
	} else
		link->wa_flags.dp_keep_receiver_powered = false;
}