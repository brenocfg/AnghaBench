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
struct myrb_hba {int /*<<< orphan*/  dcdb_pool; int /*<<< orphan*/  sg_pool; int /*<<< orphan*/  work_q; int /*<<< orphan*/  monitor_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void myrb_destroy_mempools(struct myrb_hba *cb)
{
	cancel_delayed_work_sync(&cb->monitor_work);
	destroy_workqueue(cb->work_q);

	dma_pool_destroy(cb->sg_pool);
	dma_pool_destroy(cb->dcdb_pool);
}