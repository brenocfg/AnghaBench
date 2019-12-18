#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct rtw_efuse {scalar_t__ share_ant; } ;
struct TYPE_5__ {scalar_t__ current_band_width; scalar_t__ current_channel; } ;
struct rtw_coex_dm {scalar_t__* wl_ch_info; } ;
struct TYPE_4__ {struct rtw_coex_dm dm; } ;
struct rtw_dev {TYPE_2__ hal; struct rtw_efuse efuse; TYPE_1__ coex; struct rtw_chip_info* chip; } ;
struct rtw_chip_info {scalar_t__ bt_afh_span_bw40; scalar_t__ bt_afh_span_bw20; int afh_5g_num; TYPE_3__* afh_5g; } ;
struct TYPE_6__ {scalar_t__ wl_5g_ch; scalar_t__ bt_skip_ch; scalar_t__ bt_skip_span; } ;

/* Variables and functions */
 scalar_t__ COEX_MEDIA_DISCONNECT ; 
 scalar_t__ RTW_CHANNEL_WIDTH_40 ; 
 int /*<<< orphan*/  rtw_fw_wl_ch_info (struct rtw_dev*,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void rtw_coex_update_wl_ch_info(struct rtw_dev *rtwdev, u8 type)
{
	struct rtw_chip_info *chip = rtwdev->chip;
	struct rtw_coex_dm *coex_dm = &rtwdev->coex.dm;
	struct rtw_efuse *efuse = &rtwdev->efuse;
	u8 link = 0;
	u8 center_chan = 0;
	u8 bw;
	int i;

	bw = rtwdev->hal.current_band_width;

	if (type != COEX_MEDIA_DISCONNECT)
		center_chan = rtwdev->hal.current_channel;

	if (center_chan == 0 || (efuse->share_ant && center_chan <= 14)) {
		link = 0;
	} else if (center_chan <= 14) {
		link = 0x1;

		if (bw == RTW_CHANNEL_WIDTH_40)
			bw = chip->bt_afh_span_bw40;
		else
			bw = chip->bt_afh_span_bw20;
	} else if (chip->afh_5g_num > 1) {
		for (i = 0; i < chip->afh_5g_num; i++) {
			if (center_chan == chip->afh_5g[i].wl_5g_ch) {
				link = 0x3;
				center_chan = chip->afh_5g[i].bt_skip_ch;
				bw = chip->afh_5g[i].bt_skip_span;
				break;
			}
		}
	}

	coex_dm->wl_ch_info[0] = link;
	coex_dm->wl_ch_info[1] = center_chan;
	coex_dm->wl_ch_info[2] = bw;

	rtw_fw_wl_ch_info(rtwdev, link, center_chan, bw);
}