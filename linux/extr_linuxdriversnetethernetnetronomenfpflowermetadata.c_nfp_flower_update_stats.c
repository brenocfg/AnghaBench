#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nfp_fl_stats_frame {int /*<<< orphan*/  byte_count; int /*<<< orphan*/  pkt_count; int /*<<< orphan*/  stats_con_id; int /*<<< orphan*/  stats_cookie; } ;
struct TYPE_2__ {unsigned long bytes; int /*<<< orphan*/  used; int /*<<< orphan*/  pkts; } ;
struct nfp_fl_payload {int /*<<< orphan*/  lock; TYPE_1__ stats; } ;
struct nfp_app {int dummy; } ;

/* Variables and functions */
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned long be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 struct nfp_fl_payload* nfp_flower_search_fl_table (struct nfp_app*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nfp_flower_update_stats(struct nfp_app *app, struct nfp_fl_stats_frame *stats)
{
	struct nfp_fl_payload *nfp_flow;
	unsigned long flower_cookie;

	flower_cookie = be64_to_cpu(stats->stats_cookie);

	rcu_read_lock();
	nfp_flow = nfp_flower_search_fl_table(app, flower_cookie, NULL,
					      stats->stats_con_id);
	if (!nfp_flow)
		goto exit_rcu_unlock;

	spin_lock(&nfp_flow->lock);
	nfp_flow->stats.pkts += be32_to_cpu(stats->pkt_count);
	nfp_flow->stats.bytes += be64_to_cpu(stats->byte_count);
	nfp_flow->stats.used = jiffies;
	spin_unlock(&nfp_flow->lock);

exit_rcu_unlock:
	rcu_read_unlock();
}