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

/* Variables and functions */
#define  HW_DESC_OWN 133 
#define  HW_DESC_RXBUFF_ADDR 132 
#define  HW_DESC_RXERO 131 
#define  HW_DESC_RXOWN 130 
#define  HW_DESC_RXPKT_LEN 129 
#define  HW_DESC_TX_NEXTDESC_ADDR 128 
 int /*<<< orphan*/  SET_RX_DESC_BUFF_ADDR (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_RX_DESC_EOR (int*,int) ; 
 int /*<<< orphan*/  SET_RX_DESC_OWN (int*,int) ; 
 int /*<<< orphan*/  SET_RX_DESC_PKT_LEN (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_NEXT_DESC_ADDRESS (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_OWN (int*,int) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 int /*<<< orphan*/  wmb () ; 

void rtl92de_set_desc(struct ieee80211_hw *hw, u8 *pdesc, bool istx,
		      u8 desc_name, u8 *val)
{
	if (istx) {
		switch (desc_name) {
		case HW_DESC_OWN:
			wmb();
			SET_TX_DESC_OWN(pdesc, 1);
			break;
		case HW_DESC_TX_NEXTDESC_ADDR:
			SET_TX_DESC_NEXT_DESC_ADDRESS(pdesc, *(u32 *) val);
			break;
		default:
			WARN_ONCE(true, "rtl8192de: ERR txdesc :%d not processed\n",
				  desc_name);
			break;
		}
	} else {
		switch (desc_name) {
		case HW_DESC_RXOWN:
			wmb();
			SET_RX_DESC_OWN(pdesc, 1);
			break;
		case HW_DESC_RXBUFF_ADDR:
			SET_RX_DESC_BUFF_ADDR(pdesc, *(u32 *) val);
			break;
		case HW_DESC_RXPKT_LEN:
			SET_RX_DESC_PKT_LEN(pdesc, *(u32 *) val);
			break;
		case HW_DESC_RXERO:
			SET_RX_DESC_EOR(pdesc, 1);
			break;
		default:
			WARN_ONCE(true, "rtl8192de: ERR rxdesc :%d not processed\n",
				  desc_name);
			break;
		}
	}
}