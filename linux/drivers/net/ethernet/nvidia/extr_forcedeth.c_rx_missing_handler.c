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
typedef  int u32 ;
struct fe_priv {int /*<<< orphan*/  swstats_rx_syncp; } ;

/* Variables and functions */
 int NV_RX_MISSEDFRAME ; 
 int /*<<< orphan*/  nv_txrx_stats_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stat_rx_missed_errors ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rx_missing_handler(u32 flags, struct fe_priv *np)
{
	if (flags & NV_RX_MISSEDFRAME) {
		u64_stats_update_begin(&np->swstats_rx_syncp);
		nv_txrx_stats_inc(stat_rx_missed_errors);
		u64_stats_update_end(&np->swstats_rx_syncp);
	}
}