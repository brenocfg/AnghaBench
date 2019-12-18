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
struct analogix_dp_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  aux; } ;

/* Variables and functions */
 unsigned char DP_PSR_IS_SUPPORTED ; 
 int /*<<< orphan*/  DP_PSR_SUPPORT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned char) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int drm_dp_dpcd_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*) ; 

__attribute__((used)) static bool analogix_dp_detect_sink_psr(struct analogix_dp_device *dp)
{
	unsigned char psr_version;
	int ret;

	ret = drm_dp_dpcd_readb(&dp->aux, DP_PSR_SUPPORT, &psr_version);
	if (ret != 1) {
		dev_err(dp->dev, "failed to get PSR version, disable it\n");
		return false;
	}

	dev_dbg(dp->dev, "Panel PSR version : %x\n", psr_version);
	return psr_version & DP_PSR_IS_SUPPORTED;
}