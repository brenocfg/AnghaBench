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
struct tp_usm_stats {int /*<<< orphan*/  drops; int /*<<< orphan*/  octets; int /*<<< orphan*/  frames; } ;
struct seq_file {struct adapter* private; } ;
struct adapter {int /*<<< orphan*/  stats_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRINT_ADAP_STATS (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t4_get_usm_stats (struct adapter*,struct tp_usm_stats*,int) ; 

__attribute__((used)) static void show_ddp_stats(struct seq_file *seq)
{
	struct adapter *adap = seq->private;
	struct tp_usm_stats stats;

	spin_lock(&adap->stats_lock);
	t4_get_usm_stats(adap, &stats, false);
	spin_unlock(&adap->stats_lock);

	PRINT_ADAP_STATS("usm_ddp_frames:", stats.frames);
	PRINT_ADAP_STATS("usm_ddp_octets:", stats.octets);
	PRINT_ADAP_STATS("usm_ddp_drops:", stats.drops);
}