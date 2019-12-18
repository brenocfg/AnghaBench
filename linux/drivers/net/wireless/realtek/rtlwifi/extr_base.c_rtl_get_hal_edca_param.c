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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  use_short_slot; } ;
struct ieee80211_vif {TYPE_1__ bss_conf; } ;
struct ieee80211_tx_queue_params {int txop; int aifs; int /*<<< orphan*/  cw_min; int /*<<< orphan*/  cw_max; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum wireless_mode { ____Placeholder_wireless_mode } wireless_mode ;

/* Variables and functions */
#define  WIRELESS_MODE_A 133 
#define  WIRELESS_MODE_AC_24G 132 
#define  WIRELESS_MODE_AC_5G 131 
#define  WIRELESS_MODE_G 130 
#define  WIRELESS_MODE_N_24G 129 
#define  WIRELESS_MODE_N_5G 128 
 int fls (int /*<<< orphan*/ ) ; 

u32 rtl_get_hal_edca_param(struct ieee80211_hw *hw,
			   struct ieee80211_vif *vif,
			   enum wireless_mode wirelessmode,
			   struct ieee80211_tx_queue_params *param)
{
	u32 reg = 0;
	u8 sifstime = 10;
	u8 slottime = 20;

	/* AIFS = AIFSN * slot time + SIFS */
	switch (wirelessmode) {
	case WIRELESS_MODE_A:
	case WIRELESS_MODE_N_24G:
	case WIRELESS_MODE_N_5G:
	case WIRELESS_MODE_AC_5G:
	case WIRELESS_MODE_AC_24G:
		sifstime = 16;
		slottime = 9;
		break;
	case WIRELESS_MODE_G:
		slottime = (vif->bss_conf.use_short_slot ? 9 : 20);
		break;
	default:
		break;
	}

	reg |= (param->txop & 0x7FF) << 16;
	reg |= (fls(param->cw_max) & 0xF) << 12;
	reg |= (fls(param->cw_min) & 0xF) << 8;
	reg |= (param->aifs & 0x0F) * slottime + sifstime;

	return reg;
}