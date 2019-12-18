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
typedef  int /*<<< orphan*/  u32 ;
struct ufs_qcom_phy {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline
void ufs_qcom_phy_qmp_14nm_set_tx_lane_enable(struct ufs_qcom_phy *phy, u32 val)
{
	/*
	 * 14nm PHY does not have TX_LANE_ENABLE register.
	 * Implement this function so as not to propagate error to caller.
	 */
}