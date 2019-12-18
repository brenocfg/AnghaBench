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
struct sta_info {int bssratelen; int /*<<< orphan*/  bssrateset; } ;

/* Variables and functions */
 scalar_t__ IsSupportedTxCCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_basic_rate_cck ; 
 int /*<<< orphan*/  rtw_basic_rate_ofdm ; 

void update_sta_basic_rate(struct sta_info *psta, u8 wireless_mode)
{
	if (IsSupportedTxCCK(wireless_mode)) {
		/*  Only B, B/G, and B/G/N AP could use CCK rate */
		memcpy(psta->bssrateset, rtw_basic_rate_cck, 4);
		psta->bssratelen = 4;
	} else {
		memcpy(psta->bssrateset, rtw_basic_rate_ofdm, 3);
		psta->bssratelen = 3;
	}
}