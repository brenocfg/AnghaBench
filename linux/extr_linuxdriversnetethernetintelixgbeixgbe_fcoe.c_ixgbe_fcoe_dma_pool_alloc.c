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
struct ixgbe_fcoe_ddp_pool {scalar_t__ noddp_ext_buff; scalar_t__ noddp; struct dma_pool* pool; } ;
struct ixgbe_fcoe {int /*<<< orphan*/  ddp_pool; } ;
struct dma_pool {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IXGBE_FCPTR_ALIGN ; 
 int /*<<< orphan*/  IXGBE_FCPTR_MAX ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct dma_pool* dma_pool_create (char*,struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ixgbe_fcoe_ddp_pool* per_cpu_ptr (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static int ixgbe_fcoe_dma_pool_alloc(struct ixgbe_fcoe *fcoe,
				     struct device *dev,
				     unsigned int cpu)
{
	struct ixgbe_fcoe_ddp_pool *ddp_pool;
	struct dma_pool *pool;
	char pool_name[32];

	snprintf(pool_name, 32, "ixgbe_fcoe_ddp_%u", cpu);

	pool = dma_pool_create(pool_name, dev, IXGBE_FCPTR_MAX,
			       IXGBE_FCPTR_ALIGN, PAGE_SIZE);
	if (!pool)
		return -ENOMEM;

	ddp_pool = per_cpu_ptr(fcoe->ddp_pool, cpu);
	ddp_pool->pool = pool;
	ddp_pool->noddp = 0;
	ddp_pool->noddp_ext_buff = 0;

	return 0;
}