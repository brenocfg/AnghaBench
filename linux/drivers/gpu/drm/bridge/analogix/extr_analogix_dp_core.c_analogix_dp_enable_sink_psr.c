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
struct analogix_dp_device {int psr_supported; int /*<<< orphan*/  dev; int /*<<< orphan*/  aux; } ;

/* Variables and functions */
 unsigned char DP_PSR_CRC_VERIFICATION ; 
 unsigned char DP_PSR_ENABLE ; 
 int /*<<< orphan*/  DP_PSR_EN_CFG ; 
 int /*<<< orphan*/  analogix_dp_enable_psr_crc (struct analogix_dp_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int drm_dp_dpcd_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*) ; 
 int drm_dp_dpcd_writeb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static int analogix_dp_enable_sink_psr(struct analogix_dp_device *dp)
{
	unsigned char psr_en;
	int ret;

	/* Disable psr function */
	ret = drm_dp_dpcd_readb(&dp->aux, DP_PSR_EN_CFG, &psr_en);
	if (ret != 1) {
		dev_err(dp->dev, "failed to get psr config\n");
		goto end;
	}

	psr_en &= ~DP_PSR_ENABLE;
	ret = drm_dp_dpcd_writeb(&dp->aux, DP_PSR_EN_CFG, psr_en);
	if (ret != 1) {
		dev_err(dp->dev, "failed to disable panel psr\n");
		goto end;
	}

	/* Main-Link transmitter remains active during PSR active states */
	psr_en = DP_PSR_CRC_VERIFICATION;
	ret = drm_dp_dpcd_writeb(&dp->aux, DP_PSR_EN_CFG, psr_en);
	if (ret != 1) {
		dev_err(dp->dev, "failed to set panel psr\n");
		goto end;
	}

	/* Enable psr function */
	psr_en = DP_PSR_ENABLE | DP_PSR_CRC_VERIFICATION;
	ret = drm_dp_dpcd_writeb(&dp->aux, DP_PSR_EN_CFG, psr_en);
	if (ret != 1) {
		dev_err(dp->dev, "failed to set panel psr\n");
		goto end;
	}

	analogix_dp_enable_psr_crc(dp);

	dp->psr_supported = true;

	return 0;
end:
	dev_err(dp->dev, "enable psr fail, force to disable psr\n");

	return ret;
}