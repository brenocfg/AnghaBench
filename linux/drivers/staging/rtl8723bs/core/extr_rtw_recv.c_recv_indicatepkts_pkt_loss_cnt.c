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
typedef  scalar_t__ u64 ;
struct debug_priv {int /*<<< orphan*/  dbg_rx_ampdu_loss_count; } ;

/* Variables and functions */

void recv_indicatepkts_pkt_loss_cnt(struct debug_priv *pdbgpriv, u64 prev_seq, u64 current_seq)
{
	if (current_seq < prev_seq)
		pdbgpriv->dbg_rx_ampdu_loss_count += (4096 + current_seq - prev_seq);
	else
		pdbgpriv->dbg_rx_ampdu_loss_count += (current_seq - prev_seq);

}