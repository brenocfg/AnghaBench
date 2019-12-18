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
struct sk_buff {scalar_t__ data; } ;
struct rtw_tx_pkt_info {int /*<<< orphan*/  sn; int /*<<< orphan*/  report; int /*<<< orphan*/  short_gi; int /*<<< orphan*/  ls; int /*<<< orphan*/  ampdu_en; int /*<<< orphan*/  ldpc; int /*<<< orphan*/  stbc; int /*<<< orphan*/  ampdu_density; int /*<<< orphan*/  ampdu_factor; int /*<<< orphan*/  seq; int /*<<< orphan*/  bw; int /*<<< orphan*/  sec_type; int /*<<< orphan*/  use_rate; int /*<<< orphan*/  dis_rate_fallback; int /*<<< orphan*/  rate; int /*<<< orphan*/  rate_id; int /*<<< orphan*/  bmc; int /*<<< orphan*/  qsel; int /*<<< orphan*/  pkt_offset; int /*<<< orphan*/  offset; int /*<<< orphan*/  tx_pkt_size; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  SET_TX_DESC_AGG_EN (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_AMPDU_DENSITY (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_BMC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_DATARATE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_DATA_BW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_DATA_LDPC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_DATA_SHORT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_DATA_STBC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_DISDATAFB (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_LS (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_MAX_AGG_NUM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_OFFSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_PKT_OFFSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_QSEL (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_RATE_ID (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_SEC_TYPE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_SPE_RPT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_SW_DEFINE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_SW_SEQ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_TXPKTSIZE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_USE_RATE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void rtw_tx_fill_tx_desc(struct rtw_tx_pkt_info *pkt_info, struct sk_buff *skb)
{
	__le32 *txdesc = (__le32 *)skb->data;

	SET_TX_DESC_TXPKTSIZE(txdesc,  pkt_info->tx_pkt_size);
	SET_TX_DESC_OFFSET(txdesc, pkt_info->offset);
	SET_TX_DESC_PKT_OFFSET(txdesc, pkt_info->pkt_offset);
	SET_TX_DESC_QSEL(txdesc, pkt_info->qsel);
	SET_TX_DESC_BMC(txdesc, pkt_info->bmc);
	SET_TX_DESC_RATE_ID(txdesc, pkt_info->rate_id);
	SET_TX_DESC_DATARATE(txdesc, pkt_info->rate);
	SET_TX_DESC_DISDATAFB(txdesc, pkt_info->dis_rate_fallback);
	SET_TX_DESC_USE_RATE(txdesc, pkt_info->use_rate);
	SET_TX_DESC_SEC_TYPE(txdesc, pkt_info->sec_type);
	SET_TX_DESC_DATA_BW(txdesc, pkt_info->bw);
	SET_TX_DESC_SW_SEQ(txdesc, pkt_info->seq);
	SET_TX_DESC_MAX_AGG_NUM(txdesc, pkt_info->ampdu_factor);
	SET_TX_DESC_AMPDU_DENSITY(txdesc, pkt_info->ampdu_density);
	SET_TX_DESC_DATA_STBC(txdesc, pkt_info->stbc);
	SET_TX_DESC_DATA_LDPC(txdesc, pkt_info->ldpc);
	SET_TX_DESC_AGG_EN(txdesc, pkt_info->ampdu_en);
	SET_TX_DESC_LS(txdesc, pkt_info->ls);
	SET_TX_DESC_DATA_SHORT(txdesc, pkt_info->short_gi);
	SET_TX_DESC_SPE_RPT(txdesc, pkt_info->report);
	SET_TX_DESC_SW_DEFINE(txdesc, pkt_info->sn);
}