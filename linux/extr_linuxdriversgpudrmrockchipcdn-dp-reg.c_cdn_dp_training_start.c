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
typedef  int /*<<< orphan*/  event ;

/* Variables and functions */
 int /*<<< orphan*/  DPTX_READ_EVENT ; 
 int /*<<< orphan*/  DPTX_TRAINING_CONTROL ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int EQ_PHASE_FINISHED ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  LINK_TRAINING_RETRY_MS ; 
 int LINK_TRAINING_RUN ; 
 int /*<<< orphan*/  LINK_TRAINING_TIMEOUT_MS ; 
 int /*<<< orphan*/  MB_MODULE_ID_DP_TX ; 
 int cdn_dp_mailbox_read_receive (struct cdn_dp_device*,int*,int) ; 
 int cdn_dp_mailbox_send (struct cdn_dp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int cdn_dp_mailbox_validate_receive (struct cdn_dp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int cdn_dp_training_start(struct cdn_dp_device *dp)
{
	unsigned long timeout;
	u8 msg, event[2];
	int ret;

	msg = LINK_TRAINING_RUN;

	/* start training */
	ret = cdn_dp_mailbox_send(dp, MB_MODULE_ID_DP_TX, DPTX_TRAINING_CONTROL,
				  sizeof(msg), &msg);
	if (ret)
		goto err_training_start;

	timeout = jiffies + msecs_to_jiffies(LINK_TRAINING_TIMEOUT_MS);
	while (time_before(jiffies, timeout)) {
		msleep(LINK_TRAINING_RETRY_MS);
		ret = cdn_dp_mailbox_send(dp, MB_MODULE_ID_DP_TX,
					  DPTX_READ_EVENT, 0, NULL);
		if (ret)
			goto err_training_start;

		ret = cdn_dp_mailbox_validate_receive(dp, MB_MODULE_ID_DP_TX,
						      DPTX_READ_EVENT,
						      sizeof(event));
		if (ret)
			goto err_training_start;

		ret = cdn_dp_mailbox_read_receive(dp, event, sizeof(event));
		if (ret)
			goto err_training_start;

		if (event[1] & EQ_PHASE_FINISHED)
			return 0;
	}

	ret = -ETIMEDOUT;

err_training_start:
	DRM_DEV_ERROR(dp->dev, "training failed: %d\n", ret);
	return ret;
}