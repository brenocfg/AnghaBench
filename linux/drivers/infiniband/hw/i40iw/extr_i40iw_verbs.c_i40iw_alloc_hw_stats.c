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
struct i40iw_sc_dev {int /*<<< orphan*/  is_pf; } ;
struct i40iw_device {struct i40iw_sc_dev sc_dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int I40IW_HW_STAT_INDEX_MAX_32 ; 
 int I40IW_HW_STAT_INDEX_MAX_64 ; 
 unsigned long RDMA_HW_STATS_DEFAULT_LIFESPAN ; 
 int /*<<< orphan*/  i40iw_hw_stat_names ; 
 struct rdma_hw_stats* rdma_alloc_hw_stats_struct (int /*<<< orphan*/ ,int,unsigned long) ; 
 struct i40iw_device* to_iwdev (struct ib_device*) ; 

__attribute__((used)) static struct rdma_hw_stats *i40iw_alloc_hw_stats(struct ib_device *ibdev,
						  u8 port_num)
{
	struct i40iw_device *iwdev = to_iwdev(ibdev);
	struct i40iw_sc_dev *dev = &iwdev->sc_dev;
	int num_counters = I40IW_HW_STAT_INDEX_MAX_32 +
		I40IW_HW_STAT_INDEX_MAX_64;
	unsigned long lifespan = RDMA_HW_STATS_DEFAULT_LIFESPAN;

	BUILD_BUG_ON(ARRAY_SIZE(i40iw_hw_stat_names) !=
		     (I40IW_HW_STAT_INDEX_MAX_32 +
		      I40IW_HW_STAT_INDEX_MAX_64));

	/*
	 * PFs get the default update lifespan, but VFs only update once
	 * per second
	 */
	if (!dev->is_pf)
		lifespan = 1000;
	return rdma_alloc_hw_stats_struct(i40iw_hw_stat_names, num_counters,
					  lifespan);
}