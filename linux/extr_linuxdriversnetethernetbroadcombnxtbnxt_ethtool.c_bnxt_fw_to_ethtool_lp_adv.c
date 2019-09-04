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
typedef  int /*<<< orphan*/  u16 ;
struct ethtool_link_ksettings {int dummy; } ;
struct bnxt_link_info {int autoneg; int /*<<< orphan*/  lp_pause; int /*<<< orphan*/  lp_auto_link_speeds; } ;

/* Variables and functions */
 int BNXT_AUTONEG_FLOW_CTRL ; 
 int /*<<< orphan*/  BNXT_FW_TO_ETHTOOL_SPDS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ethtool_link_ksettings*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lp_advertising ; 

__attribute__((used)) static void bnxt_fw_to_ethtool_lp_adv(struct bnxt_link_info *link_info,
				struct ethtool_link_ksettings *lk_ksettings)
{
	u16 fw_speeds = link_info->lp_auto_link_speeds;
	u8 fw_pause = 0;

	if (link_info->autoneg & BNXT_AUTONEG_FLOW_CTRL)
		fw_pause = link_info->lp_pause;

	BNXT_FW_TO_ETHTOOL_SPDS(fw_speeds, fw_pause, lk_ksettings,
				lp_advertising);
}