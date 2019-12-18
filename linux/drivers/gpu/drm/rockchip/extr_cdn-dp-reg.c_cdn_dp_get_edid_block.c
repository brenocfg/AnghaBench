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
typedef  int /*<<< orphan*/  reg ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  DPTX_GET_EDID ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 int /*<<< orphan*/  MB_MODULE_ID_DP_TX ; 
 int cdn_dp_mailbox_read_receive (struct cdn_dp_device*,int*,size_t) ; 
 int cdn_dp_mailbox_send (struct cdn_dp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int cdn_dp_mailbox_validate_receive (struct cdn_dp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int cdn_dp_get_edid_block(void *data, u8 *edid,
			  unsigned int block, size_t length)
{
	struct cdn_dp_device *dp = data;
	u8 msg[2], reg[2], i;
	int ret;

	for (i = 0; i < 4; i++) {
		msg[0] = block / 2;
		msg[1] = block % 2;

		ret = cdn_dp_mailbox_send(dp, MB_MODULE_ID_DP_TX, DPTX_GET_EDID,
					  sizeof(msg), msg);
		if (ret)
			continue;

		ret = cdn_dp_mailbox_validate_receive(dp, MB_MODULE_ID_DP_TX,
						      DPTX_GET_EDID,
						      sizeof(reg) + length);
		if (ret)
			continue;

		ret = cdn_dp_mailbox_read_receive(dp, reg, sizeof(reg));
		if (ret)
			continue;

		ret = cdn_dp_mailbox_read_receive(dp, edid, length);
		if (ret)
			continue;

		if (reg[0] == length && reg[1] == block / 2)
			break;
	}

	if (ret)
		DRM_DEV_ERROR(dp->dev, "get block[%d] edid failed: %d\n", block,
			      ret);

	return ret;
}