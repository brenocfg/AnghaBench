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
typedef  size_t u32 ;

/* Variables and functions */
 int CHANLIST_ATTR_ID ; 
 int GO_INTENT_ATTR_ID ; 
 int OPERCHAN_ATTR_ID ; 
 int WILC_INVALID_CHANNEL ; 
 int /*<<< orphan*/  wilc_wfi_cfg_parse_ch_attr (int*,int,int,int) ; 

__attribute__((used)) static void wilc_wfi_cfg_parse_tx_action(u8 *buf, u32 len, bool oper_ch,
					 u8 iftype, u8 sta_ch)
{
	u32 index = 0;
	u8 op_channel_attr_index = 0;
	u8 channel_list_attr_index = 0;

	while (index < len) {
		if (buf[index] == GO_INTENT_ATTR_ID) {
			buf[index + 3] = (buf[index + 3]  & 0x01) | (0x0f << 1);

			break;
		}

		if (buf[index] ==  CHANLIST_ATTR_ID)
			channel_list_attr_index = index;
		else if (buf[index] ==  OPERCHAN_ATTR_ID)
			op_channel_attr_index = index;
		index += buf[index + 1] + 3;
	}
	if (sta_ch != WILC_INVALID_CHANNEL && oper_ch)
		wilc_wfi_cfg_parse_ch_attr(buf, channel_list_attr_index,
					   op_channel_attr_index, sta_ch);
}