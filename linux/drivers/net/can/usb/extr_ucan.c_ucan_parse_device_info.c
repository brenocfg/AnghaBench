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
typedef  int u16 ;
struct TYPE_4__ {void* freq; } ;
struct TYPE_6__ {int /*<<< orphan*/  ctrlmode_supported; TYPE_1__ clock; } ;
struct can_bittiming_const {void* brp_inc; void* brp_max; void* brp_min; int /*<<< orphan*/  sjw_max; int /*<<< orphan*/  tseg2_max; int /*<<< orphan*/  tseg2_min; int /*<<< orphan*/  tseg1_max; int /*<<< orphan*/  tseg1_min; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_fifo; struct can_bittiming_const bittiming_const; } ;
struct ucan_priv {TYPE_3__ can; TYPE_2__ device_info; } ;
struct ucan_ctl_cmd_device_info {int /*<<< orphan*/  ctrlmodes; int /*<<< orphan*/  brp_inc; int /*<<< orphan*/  brp_max; int /*<<< orphan*/  brp_min; int /*<<< orphan*/  sjw_max; int /*<<< orphan*/  tseg2_max; int /*<<< orphan*/  tseg2_min; int /*<<< orphan*/  tseg1_max; int /*<<< orphan*/  tseg1_min; int /*<<< orphan*/  tx_fifo; int /*<<< orphan*/  freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_CTRLMODE_3_SAMPLES ; 
 int /*<<< orphan*/  CAN_CTRLMODE_BERR_REPORTING ; 
 int /*<<< orphan*/  CAN_CTRLMODE_LISTENONLY ; 
 int /*<<< orphan*/  CAN_CTRLMODE_LOOPBACK ; 
 int /*<<< orphan*/  CAN_CTRLMODE_ONE_SHOT ; 
 int UCAN_MODE_3_SAMPLES ; 
 int UCAN_MODE_BERR_REPORT ; 
 int UCAN_MODE_LOOPBACK ; 
 int UCAN_MODE_ONE_SHOT ; 
 int UCAN_MODE_SILENT ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void ucan_parse_device_info(struct ucan_priv *up,
				   struct ucan_ctl_cmd_device_info *device_info)
{
	struct can_bittiming_const *bittiming =
		&up->device_info.bittiming_const;
	u16 ctrlmodes;

	/* store the data */
	up->can.clock.freq = le32_to_cpu(device_info->freq);
	up->device_info.tx_fifo = device_info->tx_fifo;
	strcpy(bittiming->name, "ucan");
	bittiming->tseg1_min = device_info->tseg1_min;
	bittiming->tseg1_max = device_info->tseg1_max;
	bittiming->tseg2_min = device_info->tseg2_min;
	bittiming->tseg2_max = device_info->tseg2_max;
	bittiming->sjw_max = device_info->sjw_max;
	bittiming->brp_min = le32_to_cpu(device_info->brp_min);
	bittiming->brp_max = le32_to_cpu(device_info->brp_max);
	bittiming->brp_inc = le16_to_cpu(device_info->brp_inc);

	ctrlmodes = le16_to_cpu(device_info->ctrlmodes);

	up->can.ctrlmode_supported = 0;

	if (ctrlmodes & UCAN_MODE_LOOPBACK)
		up->can.ctrlmode_supported |= CAN_CTRLMODE_LOOPBACK;
	if (ctrlmodes & UCAN_MODE_SILENT)
		up->can.ctrlmode_supported |= CAN_CTRLMODE_LISTENONLY;
	if (ctrlmodes & UCAN_MODE_3_SAMPLES)
		up->can.ctrlmode_supported |= CAN_CTRLMODE_3_SAMPLES;
	if (ctrlmodes & UCAN_MODE_ONE_SHOT)
		up->can.ctrlmode_supported |= CAN_CTRLMODE_ONE_SHOT;
	if (ctrlmodes & UCAN_MODE_BERR_REPORT)
		up->can.ctrlmode_supported |= CAN_CTRLMODE_BERR_REPORTING;
}