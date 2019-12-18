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
struct sk_buff {int dummy; } ;
struct rdma_hw_stats {int num_counters; int /*<<< orphan*/ * value; int /*<<< orphan*/ * names; } ;
struct rdma_counter {struct rdma_hw_stats* stats; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  RDMA_NLDEV_ATTR_STAT_HWCOUNTERS ; 
 scalar_t__ fill_stat_hwcounter_entry (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fill_stat_counter_hwcounters(struct sk_buff *msg,
					struct rdma_counter *counter)
{
	struct rdma_hw_stats *st = counter->stats;
	struct nlattr *table_attr;
	int i;

	table_attr = nla_nest_start(msg, RDMA_NLDEV_ATTR_STAT_HWCOUNTERS);
	if (!table_attr)
		return -EMSGSIZE;

	for (i = 0; i < st->num_counters; i++)
		if (fill_stat_hwcounter_entry(msg, st->names[i], st->value[i]))
			goto err;

	nla_nest_end(msg, table_attr);
	return 0;

err:
	nla_nest_cancel(msg, table_attr);
	return -EMSGSIZE;
}