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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;

/* Variables and functions */
 int ADVERTISED_10000baseT_Full ; 
 int ADVERTISED_1000baseT_Full ; 
 int ADVERTISED_100baseT_Full ; 
 int ADVERTISED_2500baseX_Full ; 
 int ADVERTISED_40000baseCR4_Full ; 
 int ADVERTISED_Asym_Pause ; 
 int ADVERTISED_Pause ; 
 int BNXT_LINK_PAUSE_BOTH ; 
 int BNXT_LINK_PAUSE_RX ; 
 int BNXT_LINK_PAUSE_TX ; 
 int BNXT_LINK_SPEED_MSK_100MB ; 
 int BNXT_LINK_SPEED_MSK_10GB ; 
 int BNXT_LINK_SPEED_MSK_1GB ; 
 int BNXT_LINK_SPEED_MSK_2_5GB ; 
 int BNXT_LINK_SPEED_MSK_40GB ; 

u32 _bnxt_fw_to_ethtool_adv_spds(u16 fw_speeds, u8 fw_pause)
{
	u32 speed_mask = 0;

	/* TODO: support 25GB, 40GB, 50GB with different cable type */
	/* set the advertised speeds */
	if (fw_speeds & BNXT_LINK_SPEED_MSK_100MB)
		speed_mask |= ADVERTISED_100baseT_Full;
	if (fw_speeds & BNXT_LINK_SPEED_MSK_1GB)
		speed_mask |= ADVERTISED_1000baseT_Full;
	if (fw_speeds & BNXT_LINK_SPEED_MSK_2_5GB)
		speed_mask |= ADVERTISED_2500baseX_Full;
	if (fw_speeds & BNXT_LINK_SPEED_MSK_10GB)
		speed_mask |= ADVERTISED_10000baseT_Full;
	if (fw_speeds & BNXT_LINK_SPEED_MSK_40GB)
		speed_mask |= ADVERTISED_40000baseCR4_Full;

	if ((fw_pause & BNXT_LINK_PAUSE_BOTH) == BNXT_LINK_PAUSE_BOTH)
		speed_mask |= ADVERTISED_Pause;
	else if (fw_pause & BNXT_LINK_PAUSE_TX)
		speed_mask |= ADVERTISED_Asym_Pause;
	else if (fw_pause & BNXT_LINK_PAUSE_RX)
		speed_mask |= ADVERTISED_Pause | ADVERTISED_Asym_Pause;

	return speed_mask;
}