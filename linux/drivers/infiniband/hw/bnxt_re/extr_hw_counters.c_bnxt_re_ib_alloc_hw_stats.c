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
struct rdma_hw_stats {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ BNXT_RE_NUM_COUNTERS ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  RDMA_HW_STATS_DEFAULT_LIFESPAN ; 
 int /*<<< orphan*/  bnxt_re_stat_name ; 
 struct rdma_hw_stats* rdma_alloc_hw_stats_struct (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

struct rdma_hw_stats *bnxt_re_ib_alloc_hw_stats(struct ib_device *ibdev,
						u8 port_num)
{
	BUILD_BUG_ON(ARRAY_SIZE(bnxt_re_stat_name) != BNXT_RE_NUM_COUNTERS);
	/* We support only per port stats */
	if (!port_num)
		return NULL;

	return rdma_alloc_hw_stats_struct(bnxt_re_stat_name,
					  ARRAY_SIZE(bnxt_re_stat_name),
					  RDMA_HW_STATS_DEFAULT_LIFESPAN);
}