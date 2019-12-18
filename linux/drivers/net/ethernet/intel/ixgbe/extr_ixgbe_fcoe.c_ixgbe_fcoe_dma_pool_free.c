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
struct ixgbe_fcoe_ddp_pool {int /*<<< orphan*/ * pool; } ;
struct ixgbe_fcoe {int /*<<< orphan*/  ddp_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ *) ; 
 struct ixgbe_fcoe_ddp_pool* per_cpu_ptr (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void ixgbe_fcoe_dma_pool_free(struct ixgbe_fcoe *fcoe, unsigned int cpu)
{
	struct ixgbe_fcoe_ddp_pool *ddp_pool;

	ddp_pool = per_cpu_ptr(fcoe->ddp_pool, cpu);
	dma_pool_destroy(ddp_pool->pool);
	ddp_pool->pool = NULL;
}