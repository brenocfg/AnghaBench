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
typedef  int /*<<< orphan*/  u32 ;
struct ieee80211_hw {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  DESC_RATE1M ; 
 int /*<<< orphan*/  QSLT_MGNT ; 
 int /*<<< orphan*/  RTL_TX_HEADER_SIZE ; 
 int /*<<< orphan*/  _rtl_tx_desc_checksum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tx_desc_first_seg (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_hwseq_en (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_last_seg (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_nav_use_hdr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tx_desc_own (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_tx_desc_pkt_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tx_desc_pkt_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tx_desc_queue_sel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tx_desc_tx_rate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tx_desc_use_rate (int /*<<< orphan*/ *,int) ; 

void rtl92cu_fill_fake_txdesc(struct ieee80211_hw *hw, u8 *pdesc8,
			      u32 buffer_len, bool is_pspoll)
{
	__le32 *pdesc = (__le32 *)pdesc8;

	/* Clear all status */
	memset(pdesc, 0, RTL_TX_HEADER_SIZE);
	set_tx_desc_first_seg(pdesc, 1); /* bFirstSeg; */
	set_tx_desc_last_seg(pdesc, 1); /* bLastSeg; */
	set_tx_desc_offset(pdesc, RTL_TX_HEADER_SIZE); /* Offset = 32 */
	set_tx_desc_pkt_size(pdesc, buffer_len); /* Buffer size + command hdr */
	set_tx_desc_queue_sel(pdesc, QSLT_MGNT); /* Fixed queue of Mgnt queue */
	/* Set NAVUSEHDR to prevent Ps-poll AId filed to be changed to error
	 * vlaue by Hw. */
	if (is_pspoll) {
		set_tx_desc_nav_use_hdr(pdesc, 1);
	} else {
		set_tx_desc_hwseq_en(pdesc, 1); /* Hw set sequence number */
		set_tx_desc_pkt_id(pdesc, BIT(3)); /* set bit3 to 1. */
	}
	set_tx_desc_use_rate(pdesc, 1); /* use data rate which is set by Sw */
	set_tx_desc_own(pdesc, 1);
	set_tx_desc_tx_rate(pdesc, DESC_RATE1M);
	_rtl_tx_desc_checksum(pdesc);
}