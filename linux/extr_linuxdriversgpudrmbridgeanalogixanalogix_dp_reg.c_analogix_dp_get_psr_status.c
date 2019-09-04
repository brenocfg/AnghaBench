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
typedef  scalar_t__ u8 ;
struct analogix_dp_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  aux; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_PSR_STATUS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ drm_dp_dpcd_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static ssize_t analogix_dp_get_psr_status(struct analogix_dp_device *dp)
{
	ssize_t val;
	u8 status;

	val = drm_dp_dpcd_readb(&dp->aux, DP_PSR_STATUS, &status);
	if (val < 0) {
		dev_err(dp->dev, "PSR_STATUS read failed ret=%zd", val);
		return val;
	}
	return status;
}