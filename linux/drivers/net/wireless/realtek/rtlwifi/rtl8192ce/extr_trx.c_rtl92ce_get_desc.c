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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ieee80211_hw {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
#define  HW_DESC_OWN 131 
#define  HW_DESC_RXBUFF_ADDR 130 
#define  HW_DESC_RXPKT_LEN 129 
#define  HW_DESC_TXBUFF_ADDR 128 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 int /*<<< orphan*/  get_rx_desc_buff_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_rx_desc_own (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_rx_desc_pkt_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_tx_desc_own (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_tx_desc_tx_buffer_address (int /*<<< orphan*/ *) ; 

u64 rtl92ce_get_desc(struct ieee80211_hw *hw, u8 *p_desc8,
		     bool istx, u8 desc_name)
{
	u32 ret = 0;
	__le32 *p_desc = (__le32 *)p_desc8;

	if (istx) {
		switch (desc_name) {
		case HW_DESC_OWN:
			ret = get_tx_desc_own(p_desc);
			break;
		case HW_DESC_TXBUFF_ADDR:
			ret = get_tx_desc_tx_buffer_address(p_desc);
			break;
		default:
			WARN_ONCE(true, "rtl8192ce: ERR txdesc :%d not processed\n",
				  desc_name);
			break;
		}
	} else {
		switch (desc_name) {
		case HW_DESC_OWN:
			ret = get_rx_desc_own(p_desc);
			break;
		case HW_DESC_RXPKT_LEN:
			ret = get_rx_desc_pkt_len(p_desc);
			break;
		case HW_DESC_RXBUFF_ADDR:
			ret = get_rx_desc_buff_addr(p_desc);
			break;
		default:
			WARN_ONCE(true, "rtl8192ce: ERR rxdesc :%d not processed\n",
				  desc_name);
			break;
		}
	}
	return ret;
}