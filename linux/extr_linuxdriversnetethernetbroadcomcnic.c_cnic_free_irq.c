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
struct cnic_local {int /*<<< orphan*/  cnic_irq_task; int /*<<< orphan*/  (* disable_int_sync ) (struct cnic_dev*) ;struct cnic_eth_dev* ethdev; } ;
struct cnic_eth_dev {int drv_state; TYPE_1__* irq_arr; } ;
struct cnic_dev {struct cnic_local* cnic_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int CNIC_DRV_STATE_USING_MSIX ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct cnic_dev*) ; 
 int /*<<< orphan*/  stub1 (struct cnic_dev*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cnic_free_irq(struct cnic_dev *dev)
{
	struct cnic_local *cp = dev->cnic_priv;
	struct cnic_eth_dev *ethdev = cp->ethdev;

	if (ethdev->drv_state & CNIC_DRV_STATE_USING_MSIX) {
		cp->disable_int_sync(dev);
		tasklet_kill(&cp->cnic_irq_task);
		free_irq(ethdev->irq_arr[0].vector, dev);
	}
}