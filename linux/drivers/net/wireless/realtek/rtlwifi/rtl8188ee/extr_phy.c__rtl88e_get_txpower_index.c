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
struct rtl_efuse {int** txpwrlevel_cck; int** txpwrlevel_ht40_1s; int** txpwr_ht20diff; int** txpwr_legacyhtdiff; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int RF90_PATH_A ; 
 int RF90_PATH_B ; 
 int /*<<< orphan*/  handle_path_a (struct rtl_efuse*,int,int*,int*,int*,int*) ; 
 struct rtl_efuse* rtl_efuse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl88e_get_txpower_index(struct ieee80211_hw *hw, u8 channel,
				      u8 *cckpowerlevel, u8 *ofdmpowerlevel,
				      u8 *bw20powerlevel, u8 *bw40powerlevel)
{
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u8 index = (channel - 1);
	u8 rf_path = 0;

	for (rf_path = 0; rf_path < 2; rf_path++) {
		if (rf_path == RF90_PATH_A) {
			handle_path_a(rtlefuse, index, cckpowerlevel,
				      ofdmpowerlevel, bw20powerlevel,
				      bw40powerlevel);
		} else if (rf_path == RF90_PATH_B) {
			cckpowerlevel[RF90_PATH_B] =
			  rtlefuse->txpwrlevel_cck[RF90_PATH_B][index];
			bw20powerlevel[RF90_PATH_B] =
			  rtlefuse->txpwrlevel_ht40_1s[RF90_PATH_B][index] +
			  rtlefuse->txpwr_ht20diff[RF90_PATH_B][index];
			ofdmpowerlevel[RF90_PATH_B] =
			  rtlefuse->txpwrlevel_ht40_1s[RF90_PATH_B][index] +
			  rtlefuse->txpwr_legacyhtdiff[RF90_PATH_B][index];
			bw40powerlevel[RF90_PATH_B] =
			  rtlefuse->txpwrlevel_ht40_1s[RF90_PATH_B][index];
		}
	}

}