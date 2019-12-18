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
typedef  int u8 ;
struct cdn_dp_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  AUX_HOST_INVERT ; 
 int CDN_DP_MAX_LINK_RATE ; 
 int /*<<< orphan*/  DPTX_SET_HOST_CAPABILITIES ; 
 int /*<<< orphan*/  DP_AUX_SWAP_INVERSION_CONTROL ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int ENHANCED ; 
 int FAST_LT_NOT_SUPPORT ; 
 int LANE_MAPPING_FLIPPED ; 
 int LANE_MAPPING_NORMAL ; 
 int /*<<< orphan*/  MB_MODULE_ID_DP_TX ; 
 int PRE_EMPHASIS_LEVEL_3 ; 
 int PTS1 ; 
 int PTS2 ; 
 int PTS3 ; 
 int PTS4 ; 
 int SCRAMBLER_EN ; 
 int VOLTAGE_LEVEL_2 ; 
 int cdn_dp_mailbox_send (struct cdn_dp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int cdn_dp_reg_write (struct cdn_dp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cdn_dp_set_host_cap(struct cdn_dp_device *dp, u8 lanes, bool flip)
{
	u8 msg[8];
	int ret;

	msg[0] = CDN_DP_MAX_LINK_RATE;
	msg[1] = lanes | SCRAMBLER_EN;
	msg[2] = VOLTAGE_LEVEL_2;
	msg[3] = PRE_EMPHASIS_LEVEL_3;
	msg[4] = PTS1 | PTS2 | PTS3 | PTS4;
	msg[5] = FAST_LT_NOT_SUPPORT;
	msg[6] = flip ? LANE_MAPPING_FLIPPED : LANE_MAPPING_NORMAL;
	msg[7] = ENHANCED;

	ret = cdn_dp_mailbox_send(dp, MB_MODULE_ID_DP_TX,
				  DPTX_SET_HOST_CAPABILITIES,
				  sizeof(msg), msg);
	if (ret)
		goto err_set_host_cap;

	ret = cdn_dp_reg_write(dp, DP_AUX_SWAP_INVERSION_CONTROL,
			       AUX_HOST_INVERT);

err_set_host_cap:
	if (ret)
		DRM_DEV_ERROR(dp->dev, "set host cap failed: %d\n", ret);
	return ret;
}