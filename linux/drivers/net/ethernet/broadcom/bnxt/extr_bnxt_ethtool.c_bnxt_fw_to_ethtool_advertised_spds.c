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
struct bnxt_link_info {int autoneg; int /*<<< orphan*/  auto_pause_setting; int /*<<< orphan*/  advertising; } ;

/* Variables and functions */
 int BNXT_AUTONEG_FLOW_CTRL ; 
 int /*<<< orphan*/  BNXT_FW_TO_ETHTOOL_SPDS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ethtool_link_ksettings*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  advertising ; 

__attribute__((used)) static void bnxt_fw_to_ethtool_advertised_spds(struct bnxt_link_info *link_info,
				struct ethtool_link_ksettings *lk_ksettings)
{
	u16 fw_speeds = link_info->advertising;
	u8 fw_pause = 0;

	if (link_info->autoneg & BNXT_AUTONEG_FLOW_CTRL)
		fw_pause = link_info->auto_pause_setting;

	BNXT_FW_TO_ETHTOOL_SPDS(fw_speeds, fw_pause, lk_ksettings, advertising);
}