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
struct tp_err_stats {int dummy; } ;
struct seq_file {struct adapter* private; } ;
struct adapter {int /*<<< orphan*/  stats_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRINT_CH_STATS (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdr_in_errs ; 
 int /*<<< orphan*/  mac_in_errs ; 
 int /*<<< orphan*/  ofld_chan_drops ; 
 int /*<<< orphan*/  ofld_vlan_drops ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t4_tp_get_err_stats (struct adapter*,struct tp_err_stats*,int) ; 
 int /*<<< orphan*/  tcp6_in_errs ; 
 int /*<<< orphan*/  tcp_in_errs ; 
 int /*<<< orphan*/  tnl_cong_drops ; 
 int /*<<< orphan*/  tnl_tx_drops ; 

__attribute__((used)) static void show_tp_err_channel_stats(struct seq_file *seq)
{
	struct adapter *adap = seq->private;
	struct tp_err_stats stats;
	u8 i;

	spin_lock(&adap->stats_lock);
	t4_tp_get_err_stats(adap, &stats, false);
	spin_unlock(&adap->stats_lock);

	PRINT_CH_STATS("tp_mac_in_errs:", mac_in_errs);
	PRINT_CH_STATS("tp_hdr_in_errs:", hdr_in_errs);
	PRINT_CH_STATS("tp_tcp_in_errs:", tcp_in_errs);
	PRINT_CH_STATS("tp_tcp6_in_errs:", tcp6_in_errs);
	PRINT_CH_STATS("tp_tnl_cong_drops:", tnl_cong_drops);
	PRINT_CH_STATS("tp_tnl_tx_drops:", tnl_tx_drops);
	PRINT_CH_STATS("tp_ofld_vlan_drops:", ofld_vlan_drops);
	PRINT_CH_STATS("tp_ofld_chan_drops:", ofld_chan_drops);
}