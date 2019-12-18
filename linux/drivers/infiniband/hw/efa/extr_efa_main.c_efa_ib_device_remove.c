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
struct efa_dev {int /*<<< orphan*/  ibdev; int /*<<< orphan*/  edev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFA_REGS_RESET_NORMAL ; 
 int /*<<< orphan*/  efa_com_dev_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efa_release_doorbell_bar (struct efa_dev*) ; 
 int /*<<< orphan*/  ib_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ibdev_info (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void efa_ib_device_remove(struct efa_dev *dev)
{
	efa_com_dev_reset(&dev->edev, EFA_REGS_RESET_NORMAL);
	ibdev_info(&dev->ibdev, "Unregister ib device\n");
	ib_unregister_device(&dev->ibdev);
	efa_release_doorbell_bar(dev);
}