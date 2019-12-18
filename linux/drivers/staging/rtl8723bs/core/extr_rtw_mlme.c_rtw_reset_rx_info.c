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
struct debug_priv {scalar_t__ dbg_rx_ampdu_window_shift_cnt; scalar_t__ dbg_rx_dup_mgt_frame_drop_count; scalar_t__ dbg_rx_ampdu_loss_count; scalar_t__ dbg_rx_ampdu_forced_indicate_count; scalar_t__ dbg_rx_ampdu_drop_count; } ;

/* Variables and functions */

__attribute__((used)) static void rtw_reset_rx_info(struct debug_priv *pdbgpriv)
{
	pdbgpriv->dbg_rx_ampdu_drop_count = 0;
	pdbgpriv->dbg_rx_ampdu_forced_indicate_count = 0;
	pdbgpriv->dbg_rx_ampdu_loss_count = 0;
	pdbgpriv->dbg_rx_dup_mgt_frame_drop_count = 0;
	pdbgpriv->dbg_rx_ampdu_window_shift_cnt = 0;
}