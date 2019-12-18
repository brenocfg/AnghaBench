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
struct tp_cpl_stats {int dummy; } ;
struct seq_file {struct adapter* private; } ;
struct adapter {int /*<<< orphan*/  stats_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRINT_CH_STATS (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  req ; 
 int /*<<< orphan*/  rsp ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t4_tp_get_cpl_stats (struct adapter*,struct tp_cpl_stats*,int) ; 

__attribute__((used)) static void show_cpl_stats(struct seq_file *seq)
{
	struct adapter *adap = seq->private;
	struct tp_cpl_stats stats;
	u8 i;

	spin_lock(&adap->stats_lock);
	t4_tp_get_cpl_stats(adap, &stats, false);
	spin_unlock(&adap->stats_lock);

	PRINT_CH_STATS("tp_cpl_requests:", req);
	PRINT_CH_STATS("tp_cpl_responses:", rsp);
}