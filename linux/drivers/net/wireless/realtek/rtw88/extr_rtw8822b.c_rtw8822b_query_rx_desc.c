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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct rtw_rx_pkt_stat {int decrypted; int drv_info_sz; int shift; int /*<<< orphan*/  phy_status; scalar_t__ is_c2h; int /*<<< orphan*/  tsf_low; int /*<<< orphan*/  ppdu_cnt; int /*<<< orphan*/  cam_id; int /*<<< orphan*/  rate; int /*<<< orphan*/  pkt_len; int /*<<< orphan*/  crc_err; int /*<<< orphan*/  icv_err; } ;
struct rtw_dev {TYPE_1__* chip; } ;
struct ieee80211_rx_status {int dummy; } ;
struct ieee80211_hdr {int dummy; } ;
struct TYPE_2__ {int rx_pkt_desc_sz; } ;

/* Variables and functions */
 scalar_t__ GET_RX_DESC_C2H (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GET_RX_DESC_CRC32 (int /*<<< orphan*/ *) ; 
 int GET_RX_DESC_DRV_INFO_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GET_RX_DESC_ICV_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GET_RX_DESC_MACID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GET_RX_DESC_PHYST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GET_RX_DESC_PKT_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GET_RX_DESC_PPDU_CNT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GET_RX_DESC_RX_RATE (int /*<<< orphan*/ *) ; 
 int GET_RX_DESC_SHIFT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GET_RX_DESC_SWDEC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GET_RX_DESC_TSFL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct rtw_rx_pkt_stat*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  query_phy_status (struct rtw_dev*,int /*<<< orphan*/ *,struct rtw_rx_pkt_stat*) ; 
 int /*<<< orphan*/  rtw_rx_fill_rx_status (struct rtw_dev*,struct rtw_rx_pkt_stat*,struct ieee80211_hdr*,struct ieee80211_rx_status*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rtw8822b_query_rx_desc(struct rtw_dev *rtwdev, u8 *rx_desc,
				   struct rtw_rx_pkt_stat *pkt_stat,
				   struct ieee80211_rx_status *rx_status)
{
	struct ieee80211_hdr *hdr;
	u32 desc_sz = rtwdev->chip->rx_pkt_desc_sz;
	u8 *phy_status = NULL;

	memset(pkt_stat, 0, sizeof(*pkt_stat));

	pkt_stat->phy_status = GET_RX_DESC_PHYST(rx_desc);
	pkt_stat->icv_err = GET_RX_DESC_ICV_ERR(rx_desc);
	pkt_stat->crc_err = GET_RX_DESC_CRC32(rx_desc);
	pkt_stat->decrypted = !GET_RX_DESC_SWDEC(rx_desc);
	pkt_stat->is_c2h = GET_RX_DESC_C2H(rx_desc);
	pkt_stat->pkt_len = GET_RX_DESC_PKT_LEN(rx_desc);
	pkt_stat->drv_info_sz = GET_RX_DESC_DRV_INFO_SIZE(rx_desc);
	pkt_stat->shift = GET_RX_DESC_SHIFT(rx_desc);
	pkt_stat->rate = GET_RX_DESC_RX_RATE(rx_desc);
	pkt_stat->cam_id = GET_RX_DESC_MACID(rx_desc);
	pkt_stat->ppdu_cnt = GET_RX_DESC_PPDU_CNT(rx_desc);
	pkt_stat->tsf_low = GET_RX_DESC_TSFL(rx_desc);

	/* drv_info_sz is in unit of 8-bytes */
	pkt_stat->drv_info_sz *= 8;

	/* c2h cmd pkt's rx/phy status is not interested */
	if (pkt_stat->is_c2h)
		return;

	hdr = (struct ieee80211_hdr *)(rx_desc + desc_sz + pkt_stat->shift +
				       pkt_stat->drv_info_sz);
	if (pkt_stat->phy_status) {
		phy_status = rx_desc + desc_sz + pkt_stat->shift;
		query_phy_status(rtwdev, phy_status, pkt_stat);
	}

	rtw_rx_fill_rx_status(rtwdev, pkt_stat, hdr, rx_status, phy_status);
}