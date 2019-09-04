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
 int /*<<< orphan*/  DPTX_ENABLE_EVENT ; 
 int DPTX_EVENT_ENABLE_HPD ; 
 int DPTX_EVENT_ENABLE_TRAINING ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  MB_MODULE_ID_DP_TX ; 
 int cdn_dp_mailbox_send (struct cdn_dp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

int cdn_dp_event_config(struct cdn_dp_device *dp)
{
	u8 msg[5];
	int ret;

	memset(msg, 0, sizeof(msg));

	msg[0] = DPTX_EVENT_ENABLE_HPD | DPTX_EVENT_ENABLE_TRAINING;

	ret = cdn_dp_mailbox_send(dp, MB_MODULE_ID_DP_TX, DPTX_ENABLE_EVENT,
				  sizeof(msg), msg);
	if (ret)
		DRM_DEV_ERROR(dp->dev, "set event config failed: %d\n", ret);

	return ret;
}