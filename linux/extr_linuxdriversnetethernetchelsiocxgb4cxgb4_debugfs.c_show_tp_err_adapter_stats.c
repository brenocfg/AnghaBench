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
struct tp_err_stats {int /*<<< orphan*/  ofld_cong_defer; int /*<<< orphan*/  ofld_no_neigh; } ;
struct seq_file {struct adapter* private; } ;
struct adapter {int /*<<< orphan*/  stats_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRINT_ADAP_STATS (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t4_tp_get_err_stats (struct adapter*,struct tp_err_stats*,int) ; 

__attribute__((used)) static void show_tp_err_adapter_stats(struct seq_file *seq)
{
	struct adapter *adap = seq->private;
	struct tp_err_stats stats;

	spin_lock(&adap->stats_lock);
	t4_tp_get_err_stats(adap, &stats, false);
	spin_unlock(&adap->stats_lock);

	PRINT_ADAP_STATS("tp_err_ofld_no_neigh:", stats.ofld_no_neigh);
	PRINT_ADAP_STATS("tp_err_ofld_cong_defer:", stats.ofld_cong_defer);
}