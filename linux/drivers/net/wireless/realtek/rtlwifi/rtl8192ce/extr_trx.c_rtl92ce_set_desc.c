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
typedef  int /*<<< orphan*/  u32 ;
struct ieee80211_hw {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
#define  HW_DESC_OWN 133 
#define  HW_DESC_RXBUFF_ADDR 132 
#define  HW_DESC_RXERO 131 
#define  HW_DESC_RXOWN 130 
#define  HW_DESC_RXPKT_LEN 129 
#define  HW_DESC_TX_NEXTDESC_ADDR 128 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 int /*<<< orphan*/  set_rx_desc_buff_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_rx_desc_eor (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_rx_desc_own (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_rx_desc_pkt_len (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tx_desc_next_desc_address (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tx_desc_own (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wmb () ; 

void rtl92ce_set_desc(struct ieee80211_hw *hw, u8 *pdesc8, bool istx,
		      u8 desc_name, u8 *val)
{
	__le32 *pdesc = (__le32 *)pdesc8;

	if (istx) {
		switch (desc_name) {
		case HW_DESC_OWN:
			wmb();
			set_tx_desc_own(pdesc, 1);
			break;
		case HW_DESC_TX_NEXTDESC_ADDR:
			set_tx_desc_next_desc_address(pdesc, *(u32 *)val);
			break;
		default:
			WARN_ONCE(true, "rtl8192ce: ERR txdesc :%d not processed\n",
				  desc_name);
			break;
		}
	} else {
		switch (desc_name) {
		case HW_DESC_RXOWN:
			wmb();
			set_rx_desc_own(pdesc, 1);
			break;
		case HW_DESC_RXBUFF_ADDR:
			set_rx_desc_buff_addr(pdesc, *(u32 *)val);
			break;
		case HW_DESC_RXPKT_LEN:
			set_rx_desc_pkt_len(pdesc, *(u32 *)val);
			break;
		case HW_DESC_RXERO:
			set_rx_desc_eor(pdesc, 1);
			break;
		default:
			WARN_ONCE(true, "rtl8192ce: ERR rxdesc :%d not processed\n",
				  desc_name);
			break;
		}
	}
}