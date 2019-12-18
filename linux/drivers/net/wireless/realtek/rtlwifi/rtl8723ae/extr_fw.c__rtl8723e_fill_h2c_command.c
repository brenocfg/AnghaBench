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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {int /*<<< orphan*/  h2c_lock; } ;
struct rtl_priv {TYPE_1__ locks; } ;
struct rtl_hal {int h2c_setinprogress; scalar_t__ last_hmeboxnum; } ;
struct ieee80211_hw {int dummy; } ;
typedef  int /*<<< orphan*/  boxextcontent ;
typedef  scalar_t__ boxcontent ;

/* Variables and functions */
 scalar_t__ BIT (int) ; 
 int /*<<< orphan*/  COMP_CMD ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 scalar_t__ REG_HMEBOX_0 ; 
 scalar_t__ REG_HMEBOX_1 ; 
 scalar_t__ REG_HMEBOX_2 ; 
 scalar_t__ REG_HMEBOX_3 ; 
 scalar_t__ REG_HMEBOX_EXT_0 ; 
 scalar_t__ REG_HMEBOX_EXT_1 ; 
 scalar_t__ REG_HMEBOX_EXT_2 ; 
 scalar_t__ REG_HMEBOX_EXT_3 ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int _rtl8723e_check_fw_read_last_h2c (struct ieee80211_hw*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 scalar_t__ rtl_read_byte (struct rtl_priv*,int) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void _rtl8723e_fill_h2c_command(struct ieee80211_hw *hw, u8 element_id,
				       u32 cmd_len, u8 *cmdbuffer)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 boxnum;
	u16 box_reg = 0, box_extreg = 0;
	u8 u1b_tmp;
	bool isfw_read = false;
	u8 buf_index = 0;
	bool bwrite_sucess = false;
	u8 wait_h2c_limmit = 100;
	u8 wait_writeh2c_limmit = 100;
	u8 boxcontent[4], boxextcontent[2];
	u32 h2c_waitcounter = 0;
	unsigned long flag;
	u8 idx;

	RT_TRACE(rtlpriv, COMP_CMD, DBG_LOUD, "come in\n");

	while (true) {
		spin_lock_irqsave(&rtlpriv->locks.h2c_lock, flag);
		if (rtlhal->h2c_setinprogress) {
			RT_TRACE(rtlpriv, COMP_CMD, DBG_LOUD,
				 "H2C set in progress! Wait to set..element_id(%d).\n",
				 element_id);

			while (rtlhal->h2c_setinprogress) {
				spin_unlock_irqrestore(&rtlpriv->locks.h2c_lock,
						       flag);
				h2c_waitcounter++;
				RT_TRACE(rtlpriv, COMP_CMD, DBG_LOUD,
					 "Wait 100 us (%d times)...\n",
					  h2c_waitcounter);
				udelay(100);

				if (h2c_waitcounter > 1000)
					return;
				spin_lock_irqsave(&rtlpriv->locks.h2c_lock,
						  flag);
			}
			spin_unlock_irqrestore(&rtlpriv->locks.h2c_lock, flag);
		} else {
			rtlhal->h2c_setinprogress = true;
			spin_unlock_irqrestore(&rtlpriv->locks.h2c_lock, flag);
			break;
		}
	}

	while (!bwrite_sucess) {
		wait_writeh2c_limmit--;
		if (wait_writeh2c_limmit == 0) {
			pr_err("Write H2C fail because no trigger for FW INT!\n");
			break;
		}

		boxnum = rtlhal->last_hmeboxnum;
		switch (boxnum) {
		case 0:
			box_reg = REG_HMEBOX_0;
			box_extreg = REG_HMEBOX_EXT_0;
			break;
		case 1:
			box_reg = REG_HMEBOX_1;
			box_extreg = REG_HMEBOX_EXT_1;
			break;
		case 2:
			box_reg = REG_HMEBOX_2;
			box_extreg = REG_HMEBOX_EXT_2;
			break;
		case 3:
			box_reg = REG_HMEBOX_3;
			box_extreg = REG_HMEBOX_EXT_3;
			break;
		default:
			pr_err("switch case %#x not processed\n",
			       boxnum);
			break;
		}

		isfw_read = _rtl8723e_check_fw_read_last_h2c(hw, boxnum);
		while (!isfw_read) {

			wait_h2c_limmit--;
			if (wait_h2c_limmit == 0) {
				RT_TRACE(rtlpriv, COMP_CMD, DBG_LOUD,
					 "Waiting too long for FW read clear HMEBox(%d)!\n",
					 boxnum);
				break;
			}

			udelay(10);

			isfw_read = _rtl8723e_check_fw_read_last_h2c(hw,
								boxnum);
			u1b_tmp = rtl_read_byte(rtlpriv, 0x1BF);
			RT_TRACE(rtlpriv, COMP_CMD, DBG_LOUD,
				 "Waiting for FW read clear HMEBox(%d)!!! 0x1BF = %2x\n",
				 boxnum, u1b_tmp);
		}

		if (!isfw_read) {
			RT_TRACE(rtlpriv, COMP_CMD, DBG_LOUD,
				 "Write H2C register BOX[%d] fail!!!!! Fw do not read.\n",
				 boxnum);
			break;
		}

		memset(boxcontent, 0, sizeof(boxcontent));
		memset(boxextcontent, 0, sizeof(boxextcontent));
		boxcontent[0] = element_id;
		RT_TRACE(rtlpriv, COMP_CMD, DBG_LOUD,
			 "Write element_id box_reg(%4x) = %2x\n",
			  box_reg, element_id);

		switch (cmd_len) {
		case 1:
			boxcontent[0] &= ~(BIT(7));
			memcpy((u8 *)(boxcontent) + 1,
			       cmdbuffer + buf_index, 1);

			for (idx = 0; idx < 4; idx++) {
				rtl_write_byte(rtlpriv, box_reg + idx,
					       boxcontent[idx]);
			}
			break;
		case 2:
			boxcontent[0] &= ~(BIT(7));
			memcpy((u8 *)(boxcontent) + 1,
			       cmdbuffer + buf_index, 2);

			for (idx = 0; idx < 4; idx++) {
				rtl_write_byte(rtlpriv, box_reg + idx,
					       boxcontent[idx]);
			}
			break;
		case 3:
			boxcontent[0] &= ~(BIT(7));
			memcpy((u8 *)(boxcontent) + 1,
			       cmdbuffer + buf_index, 3);

			for (idx = 0; idx < 4; idx++) {
				rtl_write_byte(rtlpriv, box_reg + idx,
					       boxcontent[idx]);
			}
			break;
		case 4:
			boxcontent[0] |= (BIT(7));
			memcpy((u8 *)(boxextcontent),
			       cmdbuffer + buf_index, 2);
			memcpy((u8 *)(boxcontent) + 1,
			       cmdbuffer + buf_index + 2, 2);

			for (idx = 0; idx < 2; idx++) {
				rtl_write_byte(rtlpriv, box_extreg + idx,
					       boxextcontent[idx]);
			}

			for (idx = 0; idx < 4; idx++) {
				rtl_write_byte(rtlpriv, box_reg + idx,
					       boxcontent[idx]);
			}
			break;
		case 5:
			boxcontent[0] |= (BIT(7));
			memcpy((u8 *)(boxextcontent),
			       cmdbuffer + buf_index, 2);
			memcpy((u8 *)(boxcontent) + 1,
			       cmdbuffer + buf_index + 2, 3);

			for (idx = 0; idx < 2; idx++) {
				rtl_write_byte(rtlpriv, box_extreg + idx,
					       boxextcontent[idx]);
			}

			for (idx = 0; idx < 4; idx++) {
				rtl_write_byte(rtlpriv, box_reg + idx,
					       boxcontent[idx]);
			}
			break;
		default:
			pr_err("switch case %#x not processed\n",
			       cmd_len);
			break;
		}

		bwrite_sucess = true;

		rtlhal->last_hmeboxnum = boxnum + 1;
		if (rtlhal->last_hmeboxnum == 4)
			rtlhal->last_hmeboxnum = 0;

		RT_TRACE(rtlpriv, COMP_CMD, DBG_LOUD,
			 "pHalData->last_hmeboxnum  = %d\n",
			  rtlhal->last_hmeboxnum);
	}

	spin_lock_irqsave(&rtlpriv->locks.h2c_lock, flag);
	rtlhal->h2c_setinprogress = false;
	spin_unlock_irqrestore(&rtlpriv->locks.h2c_lock, flag);

	RT_TRACE(rtlpriv, COMP_CMD, DBG_LOUD, "go out\n");
}