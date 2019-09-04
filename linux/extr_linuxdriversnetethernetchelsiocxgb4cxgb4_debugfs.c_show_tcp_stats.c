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
struct tp_tcp_stats {int /*<<< orphan*/  tcp_retrans_segs; int /*<<< orphan*/  tcp_out_segs; int /*<<< orphan*/  tcp_in_segs; int /*<<< orphan*/  tcp_out_rsts; } ;
struct seq_file {struct adapter* private; } ;
struct adapter {int /*<<< orphan*/  stats_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRINT_ADAP_STATS (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t4_tp_get_tcp_stats (struct adapter*,struct tp_tcp_stats*,struct tp_tcp_stats*,int) ; 

__attribute__((used)) static void show_tcp_stats(struct seq_file *seq)
{
	struct adapter *adap = seq->private;
	struct tp_tcp_stats v4, v6;

	spin_lock(&adap->stats_lock);
	t4_tp_get_tcp_stats(adap, &v4, &v6, false);
	spin_unlock(&adap->stats_lock);

	PRINT_ADAP_STATS("tcp_ipv4_out_rsts:", v4.tcp_out_rsts);
	PRINT_ADAP_STATS("tcp_ipv4_in_segs:", v4.tcp_in_segs);
	PRINT_ADAP_STATS("tcp_ipv4_out_segs:", v4.tcp_out_segs);
	PRINT_ADAP_STATS("tcp_ipv4_retrans_segs:", v4.tcp_retrans_segs);
	PRINT_ADAP_STATS("tcp_ipv6_out_rsts:", v6.tcp_out_rsts);
	PRINT_ADAP_STATS("tcp_ipv6_in_segs:", v6.tcp_in_segs);
	PRINT_ADAP_STATS("tcp_ipv6_out_segs:", v6.tcp_out_segs);
	PRINT_ADAP_STATS("tcp_ipv6_retrans_segs:", v6.tcp_retrans_segs);
}