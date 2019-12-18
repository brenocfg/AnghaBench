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
struct tp_rdma_stats {int /*<<< orphan*/  rqe_dfr_pkt; int /*<<< orphan*/  rqe_dfr_mod; } ;
struct seq_file {struct adapter* private; } ;
struct adapter {int /*<<< orphan*/  stats_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRINT_ADAP_STATS (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t4_tp_get_rdma_stats (struct adapter*,struct tp_rdma_stats*,int) ; 

__attribute__((used)) static void show_rdma_stats(struct seq_file *seq)
{
	struct adapter *adap = seq->private;
	struct tp_rdma_stats stats;

	spin_lock(&adap->stats_lock);
	t4_tp_get_rdma_stats(adap, &stats, false);
	spin_unlock(&adap->stats_lock);

	PRINT_ADAP_STATS("rdma_no_rqe_mod_defer:", stats.rqe_dfr_mod);
	PRINT_ADAP_STATS("rdma_no_rqe_pkt_defer:", stats.rqe_dfr_pkt);
}