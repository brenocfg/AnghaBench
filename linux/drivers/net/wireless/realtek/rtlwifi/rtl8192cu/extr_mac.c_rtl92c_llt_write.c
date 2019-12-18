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
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 long POLLING_LLT_THRESHOLD ; 
 int /*<<< orphan*/  REG_LLT_INIT ; 
 int _LLT_INIT_ADDR (int) ; 
 int _LLT_INIT_DATA (int) ; 
 scalar_t__ _LLT_NO_ACTIVE ; 
 int _LLT_OP (int /*<<< orphan*/ ) ; 
 scalar_t__ _LLT_OP_VALUE (int) ; 
 int /*<<< orphan*/  _LLT_WRITE_ACCESS ; 
 int /*<<< orphan*/  pr_err (char*,int,scalar_t__) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_dword (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 

bool rtl92c_llt_write(struct ieee80211_hw *hw, u32 address, u32 data)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	bool status = true;
	long count = 0;
	u32 value = _LLT_INIT_ADDR(address) |
	    _LLT_INIT_DATA(data) | _LLT_OP(_LLT_WRITE_ACCESS);

	rtl_write_dword(rtlpriv, REG_LLT_INIT, value);
	do {
		value = rtl_read_dword(rtlpriv, REG_LLT_INIT);
		if (_LLT_NO_ACTIVE == _LLT_OP_VALUE(value))
			break;
		if (count > POLLING_LLT_THRESHOLD) {
			pr_err("Failed to polling write LLT done at address %d! _LLT_OP_VALUE(%x)\n",
			       address, _LLT_OP_VALUE(value));
			status = false;
			break;
		}
	} while (++count);
	return status;
}