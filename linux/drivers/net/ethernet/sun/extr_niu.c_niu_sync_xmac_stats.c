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
struct niu_xmac_stats {int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_len_errors; int /*<<< orphan*/  rx_code_violations; int /*<<< orphan*/  rx_octets; int /*<<< orphan*/  rx_hist_cnt7; int /*<<< orphan*/  rx_hist_cnt6; int /*<<< orphan*/  rx_hist_cnt5; int /*<<< orphan*/  rx_hist_cnt4; int /*<<< orphan*/  rx_hist_cnt3; int /*<<< orphan*/  rx_hist_cnt2; int /*<<< orphan*/  rx_hist_cnt1; int /*<<< orphan*/  rx_bcasts; int /*<<< orphan*/  rx_mcasts; int /*<<< orphan*/  rx_frags; int /*<<< orphan*/  rx_align_errors; int /*<<< orphan*/  rx_link_faults; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_frames; } ;
struct TYPE_2__ {struct niu_xmac_stats xmac; } ;
struct niu {TYPE_1__ mac_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINK_FAULT_CNT ; 
 int /*<<< orphan*/  RXMAC_ALIGN_ERR_CNT ; 
 int /*<<< orphan*/  RXMAC_BC_FRM_CNT ; 
 int /*<<< orphan*/  RXMAC_BT_CNT ; 
 int /*<<< orphan*/  RXMAC_CD_VIO_CNT ; 
 int /*<<< orphan*/  RXMAC_CRC_ER_CNT ; 
 int /*<<< orphan*/  RXMAC_FRAG_CNT ; 
 int /*<<< orphan*/  RXMAC_HIST_CNT1 ; 
 int /*<<< orphan*/  RXMAC_HIST_CNT2 ; 
 int /*<<< orphan*/  RXMAC_HIST_CNT3 ; 
 int /*<<< orphan*/  RXMAC_HIST_CNT4 ; 
 int /*<<< orphan*/  RXMAC_HIST_CNT5 ; 
 int /*<<< orphan*/  RXMAC_HIST_CNT6 ; 
 int /*<<< orphan*/  RXMAC_HIST_CNT7 ; 
 int /*<<< orphan*/  RXMAC_MC_FRM_CNT ; 
 int /*<<< orphan*/  RXMAC_MPSZER_CNT ; 
 int /*<<< orphan*/  TXMAC_BYTE_CNT ; 
 int /*<<< orphan*/  TXMAC_FRM_CNT ; 
 scalar_t__ nr64_mac (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void niu_sync_xmac_stats(struct niu *np)
{
	struct niu_xmac_stats *mp = &np->mac_stats.xmac;

	mp->tx_frames += nr64_mac(TXMAC_FRM_CNT);
	mp->tx_bytes += nr64_mac(TXMAC_BYTE_CNT);

	mp->rx_link_faults += nr64_mac(LINK_FAULT_CNT);
	mp->rx_align_errors += nr64_mac(RXMAC_ALIGN_ERR_CNT);
	mp->rx_frags += nr64_mac(RXMAC_FRAG_CNT);
	mp->rx_mcasts += nr64_mac(RXMAC_MC_FRM_CNT);
	mp->rx_bcasts += nr64_mac(RXMAC_BC_FRM_CNT);
	mp->rx_hist_cnt1 += nr64_mac(RXMAC_HIST_CNT1);
	mp->rx_hist_cnt2 += nr64_mac(RXMAC_HIST_CNT2);
	mp->rx_hist_cnt3 += nr64_mac(RXMAC_HIST_CNT3);
	mp->rx_hist_cnt4 += nr64_mac(RXMAC_HIST_CNT4);
	mp->rx_hist_cnt5 += nr64_mac(RXMAC_HIST_CNT5);
	mp->rx_hist_cnt6 += nr64_mac(RXMAC_HIST_CNT6);
	mp->rx_hist_cnt7 += nr64_mac(RXMAC_HIST_CNT7);
	mp->rx_octets += nr64_mac(RXMAC_BT_CNT);
	mp->rx_code_violations += nr64_mac(RXMAC_CD_VIO_CNT);
	mp->rx_len_errors += nr64_mac(RXMAC_MPSZER_CNT);
	mp->rx_crc_errors += nr64_mac(RXMAC_CRC_ER_CNT);
}