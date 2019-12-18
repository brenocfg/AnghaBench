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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
typedef  scalar_t__ tmp_4byte ;
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TX_DESC_NUM_92E ; 
 scalar_t__ calc_fifo_space (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_desc_addr_fr_q_idx (int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_dword (struct rtl_priv*,int /*<<< orphan*/ ) ; 

u16 rtl92ee_get_available_desc(struct ieee80211_hw *hw, u8 q_idx)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u16 point_diff = 0;
	u16 current_tx_read_point, current_tx_write_point;
	u32 tmp_4byte;

	tmp_4byte = rtl_read_dword(rtlpriv,
				   get_desc_addr_fr_q_idx(q_idx));
	current_tx_read_point = (u16)((tmp_4byte >> 16) & 0x0fff);
	current_tx_write_point = (u16)((tmp_4byte) & 0x0fff);

	point_diff = calc_fifo_space(current_tx_read_point,
				     current_tx_write_point,
				     TX_DESC_NUM_92E);

	return point_diff;
}