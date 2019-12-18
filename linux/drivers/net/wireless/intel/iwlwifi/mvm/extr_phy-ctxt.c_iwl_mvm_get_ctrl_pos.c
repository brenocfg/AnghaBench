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
typedef  int /*<<< orphan*/  u8 ;
struct cfg80211_chan_def {int center_freq1; TYPE_1__* chan; } ;
struct TYPE_2__ {int center_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_VHT_CTRL_POS_1_ABOVE ; 
 int /*<<< orphan*/  PHY_VHT_CTRL_POS_1_BELOW ; 
 int /*<<< orphan*/  PHY_VHT_CTRL_POS_2_ABOVE ; 
 int /*<<< orphan*/  PHY_VHT_CTRL_POS_2_BELOW ; 
 int /*<<< orphan*/  PHY_VHT_CTRL_POS_3_ABOVE ; 
 int /*<<< orphan*/  PHY_VHT_CTRL_POS_3_BELOW ; 
 int /*<<< orphan*/  PHY_VHT_CTRL_POS_4_ABOVE ; 
 int /*<<< orphan*/  PHY_VHT_CTRL_POS_4_BELOW ; 
 int /*<<< orphan*/  WARN (int,char*) ; 

u8 iwl_mvm_get_ctrl_pos(struct cfg80211_chan_def *chandef)
{
	switch (chandef->chan->center_freq - chandef->center_freq1) {
	case -70:
		return PHY_VHT_CTRL_POS_4_BELOW;
	case -50:
		return PHY_VHT_CTRL_POS_3_BELOW;
	case -30:
		return PHY_VHT_CTRL_POS_2_BELOW;
	case -10:
		return PHY_VHT_CTRL_POS_1_BELOW;
	case  10:
		return PHY_VHT_CTRL_POS_1_ABOVE;
	case  30:
		return PHY_VHT_CTRL_POS_2_ABOVE;
	case  50:
		return PHY_VHT_CTRL_POS_3_ABOVE;
	case  70:
		return PHY_VHT_CTRL_POS_4_ABOVE;
	default:
		WARN(1, "Invalid channel definition");
		/* fall through */
	case 0:
		/*
		 * The FW is expected to check the control channel position only
		 * when in HT/VHT and the channel width is not 20MHz. Return
		 * this value as the default one.
		 */
		return PHY_VHT_CTRL_POS_1_BELOW;
	}
}