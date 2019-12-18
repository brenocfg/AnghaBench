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
typedef  scalar_t__ u16 ;
struct TYPE_2__ {short rssi_threshold; } ;
struct fmdev {TYPE_1__ rx; } ;
typedef  int /*<<< orphan*/  payload ;

/* Variables and functions */
 int EINVAL ; 
 short FM_RX_RSSI_THRESHOLD_MAX ; 
 short FM_RX_RSSI_THRESHOLD_MIN ; 
 int /*<<< orphan*/  REG_WR ; 
 int /*<<< orphan*/  SEARCH_LVL_SET ; 
 int fmc_send_cmd (struct fmdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fmerr (char*) ; 

int fm_rx_set_rssi_threshold(struct fmdev *fmdev, short rssi_lvl_toset)
{
	u16 payload;
	int ret;

	if (rssi_lvl_toset < FM_RX_RSSI_THRESHOLD_MIN ||
			rssi_lvl_toset > FM_RX_RSSI_THRESHOLD_MAX) {
		fmerr("Invalid RSSI threshold level\n");
		return -EINVAL;
	}
	payload = (u16)rssi_lvl_toset;
	ret = fmc_send_cmd(fmdev, SEARCH_LVL_SET, REG_WR, &payload,
			sizeof(payload), NULL, NULL);
	if (ret < 0)
		return ret;

	fmdev->rx.rssi_threshold = rssi_lvl_toset;

	return 0;
}