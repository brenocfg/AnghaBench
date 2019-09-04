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
struct qedr_dev {int /*<<< orphan*/  ibdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_dealloc_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qedr_free_resources (struct qedr_dev*) ; 
 int /*<<< orphan*/  qedr_remove_sysfiles (struct qedr_dev*) ; 
 int /*<<< orphan*/  qedr_stop_hw (struct qedr_dev*) ; 
 int /*<<< orphan*/  qedr_sync_free_irqs (struct qedr_dev*) ; 

__attribute__((used)) static void qedr_remove(struct qedr_dev *dev)
{
	/* First unregister with stack to stop all the active traffic
	 * of the registered clients.
	 */
	qedr_remove_sysfiles(dev);
	ib_unregister_device(&dev->ibdev);

	qedr_stop_hw(dev);
	qedr_sync_free_irqs(dev);
	qedr_free_resources(dev);
	ib_dealloc_device(&dev->ibdev);
}