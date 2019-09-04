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
struct cdn_dp_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VB_ID ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int cdn_dp_reg_write_bit (struct cdn_dp_device*,int /*<<< orphan*/ ,int,int,int) ; 

int cdn_dp_audio_mute(struct cdn_dp_device *dp, bool enable)
{
	int ret;

	ret = cdn_dp_reg_write_bit(dp, DP_VB_ID, 4, 1, enable);
	if (ret)
		DRM_DEV_ERROR(dp->dev, "audio mute failed: %d\n", ret);

	return ret;
}