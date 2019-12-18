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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {int HB1; int HB2; int HB3; scalar_t__ HB0; } ;
struct dp_sdp {int* db; TYPE_1__ sdp_header; } ;
struct analogix_dp_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  aux; } ;
typedef  int /*<<< orphan*/  psr_vsc ;

/* Variables and functions */
 scalar_t__ DP_PSR_SINK_ACTIVE_RFB ; 
 int /*<<< orphan*/  DP_PSR_STATUS ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int EDP_VSC_PSR_CRC_VALUES_VALID ; 
 int EDP_VSC_PSR_STATE_ACTIVE ; 
 int /*<<< orphan*/  POWER_ALL ; 
 int analogix_dp_send_psr_spd (struct analogix_dp_device*,struct dp_sdp*,int) ; 
 int /*<<< orphan*/  analogix_dp_set_analog_power_down (struct analogix_dp_device*,int /*<<< orphan*/ ,int) ; 
 int drm_dp_dpcd_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  memset (struct dp_sdp*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int analogix_dp_enable_psr(struct analogix_dp_device *dp)
{
	struct dp_sdp psr_vsc;
	int ret;
	u8 sink;

	ret = drm_dp_dpcd_readb(&dp->aux, DP_PSR_STATUS, &sink);
	if (ret != 1)
		DRM_DEV_ERROR(dp->dev, "Failed to read psr status %d\n", ret);
	else if (sink == DP_PSR_SINK_ACTIVE_RFB)
		return 0;

	/* Prepare VSC packet as per EDP 1.4 spec, Table 6.9 */
	memset(&psr_vsc, 0, sizeof(psr_vsc));
	psr_vsc.sdp_header.HB0 = 0;
	psr_vsc.sdp_header.HB1 = 0x7;
	psr_vsc.sdp_header.HB2 = 0x2;
	psr_vsc.sdp_header.HB3 = 0x8;
	psr_vsc.db[0] = 0;
	psr_vsc.db[1] = EDP_VSC_PSR_STATE_ACTIVE | EDP_VSC_PSR_CRC_VALUES_VALID;

	ret = analogix_dp_send_psr_spd(dp, &psr_vsc, true);
	if (!ret)
		analogix_dp_set_analog_power_down(dp, POWER_ALL, true);

	return ret;
}