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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  num_lanes; int /*<<< orphan*/  rate; } ;
struct cdn_dp_device {int /*<<< orphan*/  dev; TYPE_1__ link; } ;
typedef  int /*<<< orphan*/  status ;

/* Variables and functions */
 int /*<<< orphan*/  DPTX_READ_LINK_STAT ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  MB_MODULE_ID_DP_TX ; 
 int cdn_dp_mailbox_read_receive (struct cdn_dp_device*,int /*<<< orphan*/ *,int) ; 
 int cdn_dp_mailbox_send (struct cdn_dp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int cdn_dp_mailbox_validate_receive (struct cdn_dp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  drm_dp_bw_code_to_link_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cdn_dp_get_training_status(struct cdn_dp_device *dp)
{
	u8 status[10];
	int ret;

	ret = cdn_dp_mailbox_send(dp, MB_MODULE_ID_DP_TX, DPTX_READ_LINK_STAT,
				  0, NULL);
	if (ret)
		goto err_get_training_status;

	ret = cdn_dp_mailbox_validate_receive(dp, MB_MODULE_ID_DP_TX,
					      DPTX_READ_LINK_STAT,
					      sizeof(status));
	if (ret)
		goto err_get_training_status;

	ret = cdn_dp_mailbox_read_receive(dp, status, sizeof(status));
	if (ret)
		goto err_get_training_status;

	dp->link.rate = drm_dp_bw_code_to_link_rate(status[0]);
	dp->link.num_lanes = status[1];

err_get_training_status:
	if (ret)
		DRM_DEV_ERROR(dp->dev, "get training status failed: %d\n", ret);
	return ret;
}