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
struct TYPE_2__ {int HB1; int HB2; int HB3; scalar_t__ HB0; } ;
struct edp_vsc_psr {scalar_t__ DB1; scalar_t__ DB0; TYPE_1__ sdp_header; } ;
struct analogix_dp_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  aux; int /*<<< orphan*/  psr_enable; } ;
typedef  int /*<<< orphan*/  psr_vsc ;

/* Variables and functions */
 int /*<<< orphan*/  DP_SET_POWER ; 
 int /*<<< orphan*/  DP_SET_POWER_D0 ; 
 int analogix_dp_send_psr_spd (struct analogix_dp_device*,struct edp_vsc_psr*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int drm_dp_dpcd_writeb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct edp_vsc_psr*,int /*<<< orphan*/ ,int) ; 

int analogix_dp_disable_psr(struct analogix_dp_device *dp)
{
	struct edp_vsc_psr psr_vsc;
	int ret;

	if (!dp->psr_enable)
		return 0;

	/* Prepare VSC packet as per EDP 1.4 spec, Table 6.9 */
	memset(&psr_vsc, 0, sizeof(psr_vsc));
	psr_vsc.sdp_header.HB0 = 0;
	psr_vsc.sdp_header.HB1 = 0x7;
	psr_vsc.sdp_header.HB2 = 0x2;
	psr_vsc.sdp_header.HB3 = 0x8;

	psr_vsc.DB0 = 0;
	psr_vsc.DB1 = 0;

	ret = drm_dp_dpcd_writeb(&dp->aux, DP_SET_POWER, DP_SET_POWER_D0);
	if (ret != 1) {
		dev_err(dp->dev, "Failed to set DP Power0 %d\n", ret);
		return ret;
	}

	return analogix_dp_send_psr_spd(dp, &psr_vsc, false);
}