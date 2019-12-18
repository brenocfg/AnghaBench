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
struct dtsec_cfg {int tx_pad_crc; int ptp_tsu_en; int ptp_exception_en; int /*<<< orphan*/  maximum_frame; int /*<<< orphan*/  back_to_back_ipg; int /*<<< orphan*/  min_ifg_enforcement; int /*<<< orphan*/  non_back_to_back_ipg2; int /*<<< orphan*/  non_back_to_back_ipg1; int /*<<< orphan*/  tx_pause_time_extd; int /*<<< orphan*/  preamble_len; int /*<<< orphan*/  rx_prepend; int /*<<< orphan*/  tx_pause_time; int /*<<< orphan*/  halfdup_coll_window; int /*<<< orphan*/  halfdup_retransmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_BACK_TO_BACK_IPG ; 
 int /*<<< orphan*/  DEFAULT_HALFDUP_COLL_WINDOW ; 
 int /*<<< orphan*/  DEFAULT_HALFDUP_RETRANSMIT ; 
 int /*<<< orphan*/  DEFAULT_MAXIMUM_FRAME ; 
 int /*<<< orphan*/  DEFAULT_MIN_IFG_ENFORCEMENT ; 
 int /*<<< orphan*/  DEFAULT_NON_BACK_TO_BACK_IPG1 ; 
 int /*<<< orphan*/  DEFAULT_NON_BACK_TO_BACK_IPG2 ; 
 int /*<<< orphan*/  DEFAULT_PREAMBLE_LEN ; 
 int /*<<< orphan*/  DEFAULT_RX_PREPEND ; 
 int /*<<< orphan*/  DEFAULT_TX_PAUSE_TIME ; 
 int /*<<< orphan*/  DEFAULT_TX_PAUSE_TIME_EXTD ; 

__attribute__((used)) static void set_dflts(struct dtsec_cfg *cfg)
{
	cfg->halfdup_retransmit = DEFAULT_HALFDUP_RETRANSMIT;
	cfg->halfdup_coll_window = DEFAULT_HALFDUP_COLL_WINDOW;
	cfg->tx_pad_crc = true;
	cfg->tx_pause_time = DEFAULT_TX_PAUSE_TIME;
	/* PHY address 0 is reserved (DPAA RM) */
	cfg->rx_prepend = DEFAULT_RX_PREPEND;
	cfg->ptp_tsu_en = true;
	cfg->ptp_exception_en = true;
	cfg->preamble_len = DEFAULT_PREAMBLE_LEN;
	cfg->tx_pause_time_extd = DEFAULT_TX_PAUSE_TIME_EXTD;
	cfg->non_back_to_back_ipg1 = DEFAULT_NON_BACK_TO_BACK_IPG1;
	cfg->non_back_to_back_ipg2 = DEFAULT_NON_BACK_TO_BACK_IPG2;
	cfg->min_ifg_enforcement = DEFAULT_MIN_IFG_ENFORCEMENT;
	cfg->back_to_back_ipg = DEFAULT_BACK_TO_BACK_IPG;
	cfg->maximum_frame = DEFAULT_MAXIMUM_FRAME;
}