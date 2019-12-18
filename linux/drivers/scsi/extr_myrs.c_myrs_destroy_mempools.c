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
struct myrs_hba {int /*<<< orphan*/  sense_pool; int /*<<< orphan*/  dcdb_pool; int /*<<< orphan*/  sg_pool; int /*<<< orphan*/  work_q; int /*<<< orphan*/  monitor_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void myrs_destroy_mempools(struct myrs_hba *cs)
{
	cancel_delayed_work_sync(&cs->monitor_work);
	destroy_workqueue(cs->work_q);

	dma_pool_destroy(cs->sg_pool);
	dma_pool_destroy(cs->dcdb_pool);
	dma_pool_destroy(cs->sense_pool);
}