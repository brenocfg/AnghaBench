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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  h2c_lock; } ;
struct rtl_priv {TYPE_1__ locks; } ;
struct rtl_hal {int h2c_setinprogress; int last_hmeboxnum; } ;
struct ieee80211_hw {int dummy; } ;
typedef  int /*<<< orphan*/  boxextcontent ;
typedef  scalar_t__ boxcontent ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_CMD ; 
 int /*<<< orphan*/  COMP_ERR ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int REG_CR ; 
 int REG_HMEBOX_0 ; 
 int REG_HMEBOX_1 ; 
 int REG_HMEBOX_2 ; 
 int REG_HMEBOX_3 ; 
 int REG_HMEBOX_EXT_0 ; 
 int REG_HMEBOX_EXT_1 ; 
 int REG_HMEBOX_EXT_2 ; 
 int REG_HMEBOX_EXT_3 ; 
 int REG_SYS_CFG1 ; 
 int REG_TXDMA_STATUS ; 
 int REG_TXPKT_EMPTY ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int _rtl8821ae_check_fw_read_last_h2c (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_byte (struct rtl_priv*,int) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void _rtl8821ae_fill_h2c_command(struct ieee80211_hw *hw,
					u8 element_id, u32 cmd_len,
					u8 *cmdbuffer)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 boxnum = 0;
	u16 box_reg = 0, box_extreg = 0;
	u8 u1b_tmp = 0;
	bool isfw_read = false;
	u8 buf_index = 0;
	bool bwrite_sucess = false;
	u8 wait_h2c_limmit = 100;
	/*u8 wait_writeh2c_limmit = 100;*/
	u8 boxcontent[4], boxextcontent[4];
	u32 h2c_waitcounter = 0;
	unsigned long flag = 0;
	u8 idx = 0;

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
			RT_TRACE(rtlpriv, COMP_ERR, DBG_LOUD,
				 "switch case %#x not processed\n", boxnum);
			break;
		}

		isfw_read = false;
		u1b_tmp = rtl_read_byte(rtlpriv, REG_CR);

		if (u1b_tmp != 0xEA) {
			isfw_read = true;
		} else {
			if (rtl_read_byte(rtlpriv, REG_TXDMA_STATUS) == 0xEA ||
			    rtl_read_byte(rtlpriv, REG_TXPKT_EMPTY) == 0xEA)
				rtl_write_byte(rtlpriv, REG_SYS_CFG1 + 3, 0xFF);
		}

		if (isfw_read) {
			wait_h2c_limmit = 100;
			isfw_read =
			  _rtl8821ae_check_fw_read_last_h2c(hw, boxnum);
			while (!isfw_read) {
				/*wait until Fw read*/
				wait_h2c_limmit--;
				if (wait_h2c_limmit == 0) {
					RT_TRACE(rtlpriv, COMP_CMD, DBG_LOUD,
						 "Waiting too long for FW read clear HMEBox(%d)!\n",
						 boxnum);
					break;
				}

				udelay(10);

				isfw_read =
				  _rtl8821ae_check_fw_read_last_h2c(hw, boxnum);
				u1b_tmp = rtl_read_byte(rtlpriv, 0x130);
				RT_TRACE(rtlpriv, COMP_CMD, DBG_LOUD,
					 "Waiting for FW read clear HMEBox(%d)!!! 0x130 = %2x\n",
					 boxnum, u1b_tmp);
			}
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
		case 2:
		case 3:
			/*boxcontent[0] &= ~(BIT(7));*/
			memcpy((u8 *)(boxcontent) + 1,
			       cmdbuffer + buf_index, cmd_len);

			for (idx = 0; idx < 4; idx++) {
				rtl_write_byte(rtlpriv, box_reg + idx,
					       boxcontent[idx]);
			}
			break;
		case 4:
		case 5:
		case 6:
		case 7:
			/*boxcontent[0] |= (BIT(7));*/
			memcpy((u8 *)(boxextcontent),
			       cmdbuffer + buf_index+3, cmd_len-3);
			memcpy((u8 *)(boxcontent) + 1,
			       cmdbuffer + buf_index, 3);

			for (idx = 0; idx < 4; idx++) {
				rtl_write_byte(rtlpriv, box_extreg + idx,
					       boxextcontent[idx]);
			}

			for (idx = 0; idx < 4; idx++) {
				rtl_write_byte(rtlpriv, box_reg + idx,
					       boxcontent[idx]);
			}
			break;
		default:
			RT_TRACE(rtlpriv, COMP_ERR, DBG_LOUD,
				 "switch case %#x not processed\n", cmd_len);
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