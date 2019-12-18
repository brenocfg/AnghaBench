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
struct rtw_efuse {size_t rfe_option; } ;
struct rtw_dev {struct rtw_efuse efuse; } ;
struct rtw8822b_rfe_info {int /*<<< orphan*/  (* rtw_set_channel_rfe ) (struct rtw_dev*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct rtw8822b_rfe_info*) ; 
 scalar_t__ WARN (int,char*,size_t) ; 
 struct rtw8822b_rfe_info* rtw8822b_rfe_info ; 
 int /*<<< orphan*/  rtw8822b_set_channel_bb (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw8822b_set_channel_cca (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rtw8822b_rfe_info const*) ; 
 int /*<<< orphan*/  rtw8822b_set_channel_rf (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw8822b_set_channel_rxdfir (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw8822b_toggle_igi (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_set_channel_mac (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct rtw_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtw8822b_set_channel(struct rtw_dev *rtwdev, u8 channel, u8 bw,
				 u8 primary_chan_idx)
{
	struct rtw_efuse *efuse = &rtwdev->efuse;
	const struct rtw8822b_rfe_info *rfe_info;

	if (WARN(efuse->rfe_option >= ARRAY_SIZE(rtw8822b_rfe_info),
		 "rfe_option %d is out of boundary\n", efuse->rfe_option))
		return;

	rfe_info = &rtw8822b_rfe_info[efuse->rfe_option];

	rtw8822b_set_channel_bb(rtwdev, channel, bw, primary_chan_idx);
	rtw_set_channel_mac(rtwdev, channel, bw, primary_chan_idx);
	rtw8822b_set_channel_rf(rtwdev, channel, bw);
	rtw8822b_set_channel_rxdfir(rtwdev, bw);
	rtw8822b_toggle_igi(rtwdev);
	rtw8822b_set_channel_cca(rtwdev, channel, bw, rfe_info);
	(*rfe_info->rtw_set_channel_rfe)(rtwdev, channel);
}