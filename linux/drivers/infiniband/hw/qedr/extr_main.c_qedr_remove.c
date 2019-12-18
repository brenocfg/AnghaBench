#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct qedr_dev {int /*<<< orphan*/  ibdev; int /*<<< orphan*/  cdev; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* iwarp_set_engine_affin ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 scalar_t__ IS_IWARP (struct qedr_dev*) ; 
 scalar_t__ QEDR_IS_CMT (struct qedr_dev*) ; 
 int /*<<< orphan*/  ib_dealloc_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qedr_free_resources (struct qedr_dev*) ; 
 int /*<<< orphan*/  qedr_stop_hw (struct qedr_dev*) ; 
 int /*<<< orphan*/  qedr_sync_free_irqs (struct qedr_dev*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void qedr_remove(struct qedr_dev *dev)
{
	/* First unregister with stack to stop all the active traffic
	 * of the registered clients.
	 */
	ib_unregister_device(&dev->ibdev);

	qedr_stop_hw(dev);
	qedr_sync_free_irqs(dev);
	qedr_free_resources(dev);

	if (IS_IWARP(dev) && QEDR_IS_CMT(dev))
		dev->ops->iwarp_set_engine_affin(dev->cdev, true);

	ib_dealloc_device(&dev->ibdev);
}