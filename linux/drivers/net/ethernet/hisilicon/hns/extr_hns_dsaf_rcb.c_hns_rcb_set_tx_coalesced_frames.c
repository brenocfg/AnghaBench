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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct rcb_common_cb {TYPE_1__* dsaf_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HNS_RCB_TX_PKTLINE_OFFSET ; 
 scalar_t__ RCB_CFG_PKTLINE_REG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dsaf_write_dev (struct rcb_common_cb*,scalar_t__,scalar_t__) ; 
 scalar_t__ hns_rcb_get_tx_coalesced_frames (struct rcb_common_cb*,scalar_t__) ; 

int hns_rcb_set_tx_coalesced_frames(
	struct rcb_common_cb *rcb_common, u32 port_idx, u32 coalesced_frames)
{
	u32 old_waterline =
		hns_rcb_get_tx_coalesced_frames(rcb_common, port_idx);
	u64 reg;

	if (coalesced_frames == old_waterline)
		return 0;

	if (coalesced_frames != 1) {
		dev_err(rcb_common->dsaf_dev->dev,
			"error: not support tx coalesce_frames setting!\n");
		return -EINVAL;
	}

	reg = RCB_CFG_PKTLINE_REG + (port_idx + HNS_RCB_TX_PKTLINE_OFFSET) * 4;
	dsaf_write_dev(rcb_common, reg,	coalesced_frames);
	return 0;
}