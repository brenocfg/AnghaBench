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
typedef  int u32 ;
typedef  int u16 ;
struct rtl_wow_pattern {int crc; scalar_t__ type; int* mask; } ;
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ BROADCAST_PATTERN ; 
 int /*<<< orphan*/  COMP_POWER ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  DISABLE_TRXPKT_BUF_ACCESS ; 
 int MAX_RX_DMA_BUFFER_SIZE_8812 ; 
 scalar_t__ MULTICAST_PATTERN ; 
 int /*<<< orphan*/  REG_PKTBUF_DBG_CTRL ; 
 int /*<<< orphan*/  REG_PKTBUF_DBG_DATA_H ; 
 int /*<<< orphan*/  REG_PKTBUF_DBG_DATA_L ; 
 int /*<<< orphan*/  REG_PKT_BUFF_ACCESS_CTRL ; 
 int /*<<< orphan*/  REG_RXPKTBUF_CTRL ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RXPKT_BUF_SELECT ; 
 scalar_t__ UNICAST_PATTERN ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 int WKFMCAM_ADDR_NUM ; 
 int WKFMCAM_SIZE ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_byte (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_write_word (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

void rtl8821ae_add_wowlan_pattern(struct ieee80211_hw *hw,
				  struct rtl_wow_pattern *rtl_pattern,
				  u8 index)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u32 cam = 0;
	u8 addr = 0;
	u16 rxbuf_addr;
	u8 tmp, count = 0;
	u16 cam_start;
	u16 offset;

	/* Count the WFCAM entry start offset. */

	/* RX page size = 128 byte */
	offset = MAX_RX_DMA_BUFFER_SIZE_8812 / 128;
	/* We should start from the boundry */
	cam_start = offset * 128;

	/* Enable Rx packet buffer access. */
	rtl_write_byte(rtlpriv, REG_PKT_BUFF_ACCESS_CTRL, RXPKT_BUF_SELECT);
	for (addr = 0; addr < WKFMCAM_ADDR_NUM; addr++) {
		/* Set Rx packet buffer offset.
		 * RXBufer pointer increases 1,
		 * we can access 8 bytes in Rx packet buffer.
		 * CAM start offset (unit: 1 byte) =  index*WKFMCAM_SIZE
		 * RXBufer addr = (CAM start offset +
		 *                 per entry offset of a WKFM CAM)/8
		 *	* index: The index of the wake up frame mask
		 *	* WKFMCAM_SIZE: the total size of one WKFM CAM
		 *	* per entry offset of a WKFM CAM: Addr*4 bytes
		 */
		rxbuf_addr = (cam_start + index * WKFMCAM_SIZE + addr * 4) >> 3;
		/* Set R/W start offset */
		rtl_write_word(rtlpriv, REG_PKTBUF_DBG_CTRL, rxbuf_addr);

		if (addr == 0) {
			cam = BIT(31) | rtl_pattern->crc;

			if (rtl_pattern->type == UNICAST_PATTERN)
				cam |= BIT(24);
			else if (rtl_pattern->type == MULTICAST_PATTERN)
				cam |= BIT(25);
			else if (rtl_pattern->type == BROADCAST_PATTERN)
				cam |= BIT(26);

			rtl_write_dword(rtlpriv, REG_PKTBUF_DBG_DATA_L, cam);
			RT_TRACE(rtlpriv, COMP_POWER, DBG_TRACE,
				 "WRITE entry[%d] 0x%x: %x\n", addr,
				  REG_PKTBUF_DBG_DATA_L, cam);

			/* Write to Rx packet buffer. */
			rtl_write_word(rtlpriv, REG_RXPKTBUF_CTRL, 0x0f01);
		} else if (addr == 2 || addr == 4) {/* WKFM[127:0] */
			cam = rtl_pattern->mask[addr - 2];

			rtl_write_dword(rtlpriv, REG_PKTBUF_DBG_DATA_L, cam);
			RT_TRACE(rtlpriv, COMP_POWER, DBG_TRACE,
				 "WRITE entry[%d] 0x%x: %x\n", addr,
				  REG_PKTBUF_DBG_DATA_L, cam);

			rtl_write_word(rtlpriv, REG_RXPKTBUF_CTRL, 0x0f01);
		} else if (addr == 3 || addr == 5) {/* WKFM[127:0] */
			cam = rtl_pattern->mask[addr - 2];

			rtl_write_dword(rtlpriv, REG_PKTBUF_DBG_DATA_H, cam);
			RT_TRACE(rtlpriv, COMP_POWER, DBG_TRACE,
				 "WRITE entry[%d] 0x%x: %x\n", addr,
				  REG_PKTBUF_DBG_DATA_H, cam);

			rtl_write_word(rtlpriv, REG_RXPKTBUF_CTRL, 0xf001);
		}

		count = 0;
		do {
			tmp = rtl_read_byte(rtlpriv, REG_RXPKTBUF_CTRL);
			udelay(2);
			count++;
		} while (tmp && count < 100);

		WARN_ONCE((count >= 100),
			  "rtl8821ae: Write wake up frame mask FAIL %d value!\n",
			  tmp);
	}
	/* Disable Rx packet buffer access. */
	rtl_write_byte(rtlpriv, REG_PKT_BUFF_ACCESS_CTRL,
		       DISABLE_TRXPKT_BUF_ACCESS);
}