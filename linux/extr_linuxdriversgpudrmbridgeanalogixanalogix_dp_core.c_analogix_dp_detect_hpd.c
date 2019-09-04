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
struct analogix_dp_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  force_hpd; } ;

/* Variables and functions */
 int DP_TIMEOUT_LOOP_COUNT ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  analogix_dp_force_hpd (struct analogix_dp_device*) ; 
 scalar_t__ analogix_dp_get_plug_in_status (struct analogix_dp_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int analogix_dp_detect_hpd(struct analogix_dp_device *dp)
{
	int timeout_loop = 0;

	while (timeout_loop < DP_TIMEOUT_LOOP_COUNT) {
		if (analogix_dp_get_plug_in_status(dp) == 0)
			return 0;

		timeout_loop++;
		usleep_range(1000, 1100);
	}

	/*
	 * Some edp screen do not have hpd signal, so we can't just
	 * return failed when hpd plug in detect failed, DT property
	 * "force-hpd" would indicate whether driver need this.
	 */
	if (!dp->force_hpd)
		return -ETIMEDOUT;

	/*
	 * The eDP TRM indicate that if HPD_STATUS(RO) is 0, AUX CH
	 * will not work, so we need to give a force hpd action to
	 * set HPD_STATUS manually.
	 */
	dev_dbg(dp->dev, "failed to get hpd plug status, try to force hpd\n");

	analogix_dp_force_hpd(dp);

	if (analogix_dp_get_plug_in_status(dp) != 0) {
		dev_err(dp->dev, "failed to get hpd plug in status\n");
		return -EINVAL;
	}

	dev_dbg(dp->dev, "success to get plug in status after force hpd\n");

	return 0;
}