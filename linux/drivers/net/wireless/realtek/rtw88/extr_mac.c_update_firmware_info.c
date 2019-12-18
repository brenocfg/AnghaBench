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
typedef  void* u8 ;
struct rtw_fw_state {void* sub_index; void* sub_version; void* version; void* h2c_version; TYPE_1__* firmware; } ;
struct rtw_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {void** data; } ;

/* Variables and functions */
 int FW_HDR_H2C_FMT_VER ; 
 int FW_HDR_SUBINDEX ; 
 int FW_HDR_SUBVERSION ; 
 int FW_HDR_VERSION ; 
 int /*<<< orphan*/  RTW_DBG_FW ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_dbg (struct rtw_dev*,int /*<<< orphan*/ ,char*,void*) ; 

__attribute__((used)) static void update_firmware_info(struct rtw_dev *rtwdev,
				 struct rtw_fw_state *fw)
{
	const u8 *data = fw->firmware->data;

	fw->h2c_version =
		le16_to_cpu(*((__le16 *)(data + FW_HDR_H2C_FMT_VER)));
	fw->version =
		le16_to_cpu(*((__le16 *)(data + FW_HDR_VERSION)));
	fw->sub_version = *(data + FW_HDR_SUBVERSION);
	fw->sub_index = *(data + FW_HDR_SUBINDEX);

	rtw_dbg(rtwdev, RTW_DBG_FW, "fw h2c version: %x\n", fw->h2c_version);
	rtw_dbg(rtwdev, RTW_DBG_FW, "fw version:     %x\n", fw->version);
	rtw_dbg(rtwdev, RTW_DBG_FW, "fw sub version: %x\n", fw->sub_version);
	rtw_dbg(rtwdev, RTW_DBG_FW, "fw sub index:   %x\n", fw->sub_index);
}