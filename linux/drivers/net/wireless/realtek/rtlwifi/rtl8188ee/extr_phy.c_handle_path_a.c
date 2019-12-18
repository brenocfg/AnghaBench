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
typedef  size_t u8 ;
struct rtl_efuse {size_t** txpwrlevel_cck; int** txpwr_ht20diff; size_t** txpwrlevel_ht40_1s; int** txpwr_legacyhtdiff; } ;

/* Variables and functions */
 size_t RF90_PATH_A ; 

__attribute__((used)) static void handle_path_a(struct rtl_efuse *rtlefuse, u8 index,
			  u8 *cckpowerlevel, u8 *ofdmpowerlevel,
			  u8 *bw20powerlevel, u8 *bw40powerlevel)
{
	cckpowerlevel[RF90_PATH_A] =
	    rtlefuse->txpwrlevel_cck[RF90_PATH_A][index];
		/*-8~7 */
	if (rtlefuse->txpwr_ht20diff[RF90_PATH_A][index] > 0x0f)
		bw20powerlevel[RF90_PATH_A] =
		  rtlefuse->txpwrlevel_ht40_1s[RF90_PATH_A][index] -
		  (~(rtlefuse->txpwr_ht20diff[RF90_PATH_A][index]) + 1);
	else
		bw20powerlevel[RF90_PATH_A] =
		  rtlefuse->txpwrlevel_ht40_1s[RF90_PATH_A][index] +
		  rtlefuse->txpwr_ht20diff[RF90_PATH_A][index];
	if (rtlefuse->txpwr_legacyhtdiff[RF90_PATH_A][index] > 0xf)
		ofdmpowerlevel[RF90_PATH_A] =
		  rtlefuse->txpwrlevel_ht40_1s[RF90_PATH_A][index] -
		  (~(rtlefuse->txpwr_legacyhtdiff[RF90_PATH_A][index])+1);
	else
		ofdmpowerlevel[RF90_PATH_A] =
		rtlefuse->txpwrlevel_ht40_1s[RF90_PATH_A][index] +
		  rtlefuse->txpwr_legacyhtdiff[RF90_PATH_A][index];
	bw40powerlevel[RF90_PATH_A] =
	  rtlefuse->txpwrlevel_ht40_1s[RF90_PATH_A][index];
}