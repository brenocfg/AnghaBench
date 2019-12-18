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
struct rxe_dev {int /*<<< orphan*/ * stats_counters; } ;
struct rdma_hw_stats {int /*<<< orphan*/ * value; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxe_counter_name ; 
 struct rxe_dev* to_rdev (struct ib_device*) ; 

int rxe_ib_get_hw_stats(struct ib_device *ibdev,
			struct rdma_hw_stats *stats,
			u8 port, int index)
{
	struct rxe_dev *dev = to_rdev(ibdev);
	unsigned int cnt;

	if (!port || !stats)
		return -EINVAL;

	for (cnt = 0; cnt  < ARRAY_SIZE(rxe_counter_name); cnt++)
		stats->value[cnt] = atomic64_read(&dev->stats_counters[cnt]);

	return ARRAY_SIZE(rxe_counter_name);
}