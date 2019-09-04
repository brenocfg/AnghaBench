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
struct rdma_hw_stats {int num_counters; scalar_t__ timestamp; scalar_t__ lifespan; } ;
struct ib_device {int (* get_hw_stats ) (struct ib_device*,struct rdma_hw_stats*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 scalar_t__ jiffies ; 
 int stub1 (struct ib_device*,struct rdma_hw_stats*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ time_is_after_eq_jiffies (scalar_t__) ; 

__attribute__((used)) static int update_hw_stats(struct ib_device *dev, struct rdma_hw_stats *stats,
			   u8 port_num, int index)
{
	int ret;

	if (time_is_after_eq_jiffies(stats->timestamp + stats->lifespan))
		return 0;
	ret = dev->get_hw_stats(dev, stats, port_num, index);
	if (ret < 0)
		return ret;
	if (ret == stats->num_counters)
		stats->timestamp = jiffies;

	return 0;
}