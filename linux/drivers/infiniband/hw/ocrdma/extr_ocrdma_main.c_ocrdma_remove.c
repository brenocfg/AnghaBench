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
struct ocrdma_dev {int /*<<< orphan*/  ibdev; int /*<<< orphan*/  eqd_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocrdma_cleanup_hw (struct ocrdma_dev*) ; 
 int /*<<< orphan*/  ocrdma_free_resources (struct ocrdma_dev*) ; 
 int /*<<< orphan*/  ocrdma_rem_port_stats (struct ocrdma_dev*) ; 
 int /*<<< orphan*/  ocrdma_remove_free (struct ocrdma_dev*) ; 

__attribute__((used)) static void ocrdma_remove(struct ocrdma_dev *dev)
{
	/* first unregister with stack to stop all the active traffic
	 * of the registered clients.
	 */
	cancel_delayed_work_sync(&dev->eqd_work);
	ib_unregister_device(&dev->ibdev);

	ocrdma_rem_port_stats(dev);
	ocrdma_free_resources(dev);
	ocrdma_cleanup_hw(dev);
	ocrdma_remove_free(dev);
}