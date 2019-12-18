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
typedef  int u16 ;
struct rtl_priv {TYPE_1__* cfg; } ;
struct rtl_efuse {int** efuse_map; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_2__ {int* maps; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  COMP_EFUSE ; 
 int /*<<< orphan*/  COMP_ERR ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  DBG_WARNING ; 
 size_t EFUSE_HWSET_MAX_SIZE ; 
 size_t EFUSE_INIT_MAP ; 
 size_t EFUSE_MODIFY_MAP ; 
 int /*<<< orphan*/  RT_PRINT_DATA (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  efuse_pg_packet_write (struct ieee80211_hw*,int,int,int*) ; 
 int /*<<< orphan*/  efuse_power_switch (struct ieee80211_hw*,int,int) ; 
 int /*<<< orphan*/  efuse_read_all_map (struct ieee80211_hw*,int*) ; 
 int /*<<< orphan*/  efuse_shadow_update_chk (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

bool efuse_shadow_update(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u16 i, offset, base;
	u8 word_en = 0x0F;
	u8 first_pg = false;

	RT_TRACE(rtlpriv, COMP_EFUSE, DBG_LOUD, "\n");

	if (!efuse_shadow_update_chk(hw)) {
		efuse_read_all_map(hw, &rtlefuse->efuse_map[EFUSE_INIT_MAP][0]);
		memcpy(&rtlefuse->efuse_map[EFUSE_MODIFY_MAP][0],
		       &rtlefuse->efuse_map[EFUSE_INIT_MAP][0],
		       rtlpriv->cfg->maps[EFUSE_HWSET_MAX_SIZE]);

		RT_TRACE(rtlpriv, COMP_EFUSE, DBG_LOUD,
			 "efuse out of capacity!!\n");
		return false;
	}
	efuse_power_switch(hw, true, true);

	for (offset = 0; offset < 16; offset++) {

		word_en = 0x0F;
		base = offset * 8;

		for (i = 0; i < 8; i++) {
			if (first_pg) {
				word_en &= ~(BIT(i / 2));

				rtlefuse->efuse_map[EFUSE_INIT_MAP][base + i] =
				    rtlefuse->efuse_map[EFUSE_MODIFY_MAP][base + i];
			} else {

				if (rtlefuse->efuse_map[EFUSE_INIT_MAP][base + i] !=
				    rtlefuse->efuse_map[EFUSE_MODIFY_MAP][base + i]) {
					word_en &= ~(BIT(i / 2));

					rtlefuse->efuse_map[EFUSE_INIT_MAP][base + i] =
					    rtlefuse->efuse_map[EFUSE_MODIFY_MAP][base + i];
				}
			}
		}

		if (word_en != 0x0F) {
			u8 tmpdata[8];

			memcpy(tmpdata,
			       &rtlefuse->efuse_map[EFUSE_MODIFY_MAP][base],
			       8);
			RT_PRINT_DATA(rtlpriv, COMP_INIT, DBG_LOUD,
				      "U-efuse\n", tmpdata, 8);

			if (!efuse_pg_packet_write(hw, (u8) offset, word_en,
						   tmpdata)) {
				RT_TRACE(rtlpriv, COMP_ERR, DBG_WARNING,
					 "PG section(%#x) fail!!\n", offset);
				break;
			}
		}
	}

	efuse_power_switch(hw, true, false);
	efuse_read_all_map(hw, &rtlefuse->efuse_map[EFUSE_INIT_MAP][0]);

	memcpy(&rtlefuse->efuse_map[EFUSE_MODIFY_MAP][0],
	       &rtlefuse->efuse_map[EFUSE_INIT_MAP][0],
	       rtlpriv->cfg->maps[EFUSE_HWSET_MAX_SIZE]);

	RT_TRACE(rtlpriv, COMP_EFUSE, DBG_LOUD, "\n");
	return true;
}