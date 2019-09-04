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
typedef  int /*<<< orphan*/  u8 ;
struct analogix_dp_device {int /*<<< orphan*/  aux; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_MAX_LINK_RATE ; 
 int /*<<< orphan*/  drm_dp_dpcd_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void analogix_dp_get_max_rx_bandwidth(struct analogix_dp_device *dp,
					     u8 *bandwidth)
{
	u8 data;

	/*
	 * For DP rev.1.1, Maximum link rate of Main Link lanes
	 * 0x06 = 1.62 Gbps, 0x0a = 2.7 Gbps
	 * For DP rev.1.2, Maximum link rate of Main Link lanes
	 * 0x06 = 1.62 Gbps, 0x0a = 2.7 Gbps, 0x14 = 5.4Gbps
	 */
	drm_dp_dpcd_readb(&dp->aux, DP_MAX_LINK_RATE, &data);
	*bandwidth = data;
}