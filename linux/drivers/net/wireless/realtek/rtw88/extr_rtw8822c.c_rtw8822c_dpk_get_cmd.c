#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_3__ {scalar_t__ dpk_bw; } ;
struct TYPE_4__ {TYPE_1__ dpk_info; } ;
struct rtw_dev {TYPE_2__ dm_info; } ;

/* Variables and functions */
 scalar_t__ DPK_CHANNEL_WIDTH_80 ; 
#define  RTW_DPK_DAGC 131 
#define  RTW_DPK_DO_DPK 130 
#define  RTW_DPK_DPK_ON 129 
#define  RTW_DPK_GAIN_LOSS 128 

__attribute__((used)) static u16 rtw8822c_dpk_get_cmd(struct rtw_dev *rtwdev, u8 action, u8 path)
{
	u16 cmd;
	u8 bw = rtwdev->dm_info.dpk_info.dpk_bw == DPK_CHANNEL_WIDTH_80 ? 2 : 0;

	switch (action) {
	case RTW_DPK_GAIN_LOSS:
		cmd = 0x14 + path;
		break;
	case RTW_DPK_DO_DPK:
		cmd = 0x16 + path + bw;
		break;
	case RTW_DPK_DPK_ON:
		cmd = 0x1a + path;
		break;
	case RTW_DPK_DAGC:
		cmd = 0x1c + path + bw;
		break;
	default:
		return 0;
	}

	return (cmd << 8) | 0x48;
}