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
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int LAST_ENTRY_OF_TX_PKT_BUFFER ; 
 int _rtl8821ae_llt_write (struct ieee80211_hw*,int,int) ; 

__attribute__((used)) static bool _rtl8821ae_init_llt_table(struct ieee80211_hw *hw, u32 boundary)
{
	bool status = true;
	u32 i;
	u32 txpktbuf_bndy = boundary;
	u32 last_entry_of_txpktbuf = LAST_ENTRY_OF_TX_PKT_BUFFER;

	for (i = 0 ; i < (txpktbuf_bndy - 1) ; i++) {
		status = _rtl8821ae_llt_write(hw, i , i + 1);
		if (!status)
			return status;
	}

	status = _rtl8821ae_llt_write(hw, (txpktbuf_bndy - 1), 0xFF);
	if (!status)
		return status;

	for (i = txpktbuf_bndy ; i < last_entry_of_txpktbuf ; i++) {
		status = _rtl8821ae_llt_write(hw, i, (i + 1));
		if (!status)
			return status;
	}

	status = _rtl8821ae_llt_write(hw, last_entry_of_txpktbuf,
				      txpktbuf_bndy);
	if (!status)
		return status;

	return status;
}