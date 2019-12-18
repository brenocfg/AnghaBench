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
typedef  int u32 ;
struct rtl_fw_phy_action {size_t size; int /*<<< orphan*/ * code; } ;
struct rtl_fw {int (* phy_read ) (struct rtl8169_private*,int) ;int (* mac_mcu_read ) (struct rtl8169_private*,int) ;int /*<<< orphan*/  (* mac_mcu_write ) (struct rtl8169_private*,int,int) ;int /*<<< orphan*/  (* phy_write ) (struct rtl8169_private*,int,int) ;struct rtl_fw_phy_action phy_action; } ;
struct rtl8169_private {int dummy; } ;
typedef  int /*<<< orphan*/  (* rtl_fw_write_t ) (struct rtl8169_private*,int,int) ;
typedef  int (* rtl_fw_read_t ) (struct rtl8169_private*,int) ;
typedef  enum rtl_fw_opcode { ____Placeholder_rtl_fw_opcode } rtl_fw_opcode ;

/* Variables and functions */
#define  PHY_BJMPN 140 
#define  PHY_CLEAR_READCOUNT 139 
#define  PHY_COMP_EQ_SKIPN 138 
#define  PHY_COMP_NEQ_SKIPN 137 
#define  PHY_DATA_AND 136 
#define  PHY_DATA_OR 135 
#define  PHY_DELAY_MS 134 
#define  PHY_MDIO_CHG 133 
#define  PHY_READ 132 
#define  PHY_READCOUNT_EQ_SKIP 131 
#define  PHY_SKIPN 130 
#define  PHY_WRITE 129 
#define  PHY_WRITE_PREVIOUS 128 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 

void rtl_fw_write_firmware(struct rtl8169_private *tp, struct rtl_fw *rtl_fw)
{
	struct rtl_fw_phy_action *pa = &rtl_fw->phy_action;
	rtl_fw_write_t fw_write = rtl_fw->phy_write;
	rtl_fw_read_t fw_read = rtl_fw->phy_read;
	int predata = 0, count = 0;
	size_t index;

	for (index = 0; index < pa->size; index++) {
		u32 action = le32_to_cpu(pa->code[index]);
		u32 data = action & 0x0000ffff;
		u32 regno = (action & 0x0fff0000) >> 16;
		enum rtl_fw_opcode opcode = action >> 28;

		if (!action)
			break;

		switch (opcode) {
		case PHY_READ:
			predata = fw_read(tp, regno);
			count++;
			break;
		case PHY_DATA_OR:
			predata |= data;
			break;
		case PHY_DATA_AND:
			predata &= data;
			break;
		case PHY_BJMPN:
			index -= (regno + 1);
			break;
		case PHY_MDIO_CHG:
			if (data == 0) {
				fw_write = rtl_fw->phy_write;
				fw_read = rtl_fw->phy_read;
			} else if (data == 1) {
				fw_write = rtl_fw->mac_mcu_write;
				fw_read = rtl_fw->mac_mcu_read;
			}

			break;
		case PHY_CLEAR_READCOUNT:
			count = 0;
			break;
		case PHY_WRITE:
			fw_write(tp, regno, data);
			break;
		case PHY_READCOUNT_EQ_SKIP:
			if (count == data)
				index++;
			break;
		case PHY_COMP_EQ_SKIPN:
			if (predata == data)
				index += regno;
			break;
		case PHY_COMP_NEQ_SKIPN:
			if (predata != data)
				index += regno;
			break;
		case PHY_WRITE_PREVIOUS:
			fw_write(tp, regno, predata);
			break;
		case PHY_SKIPN:
			index += regno;
			break;
		case PHY_DELAY_MS:
			mdelay(data);
			break;
		}
	}
}