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
struct qlcnic_dcb {struct qlcnic_dcb* param; struct qlcnic_dcb* cfg; int /*<<< orphan*/ * wq; int /*<<< orphan*/  aen_work; int /*<<< orphan*/  state; struct qlcnic_adapter* adapter; } ;
struct qlcnic_adapter {int /*<<< orphan*/ * dcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_DCB_AEN_MODE ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct qlcnic_dcb*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void __qlcnic_dcb_free(struct qlcnic_dcb *dcb)
{
	struct qlcnic_adapter *adapter;

	if (!dcb)
		return;

	adapter = dcb->adapter;

	while (test_bit(QLCNIC_DCB_AEN_MODE, &dcb->state))
		usleep_range(10000, 11000);

	cancel_delayed_work_sync(&dcb->aen_work);

	if (dcb->wq) {
		destroy_workqueue(dcb->wq);
		dcb->wq = NULL;
	}

	kfree(dcb->cfg);
	dcb->cfg = NULL;
	kfree(dcb->param);
	dcb->param = NULL;
	kfree(dcb);
	adapter->dcb = NULL;
}