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
struct t3cdev {int /*<<< orphan*/  type; int /*<<< orphan*/  ctl; int /*<<< orphan*/  send; int /*<<< orphan*/  ofld_dev_list; } ;
struct adapter {struct t3cdev tdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  adap2type (struct adapter*) ; 
 int /*<<< orphan*/  cxgb3_set_dummy_ops (struct t3cdev*) ; 
 int /*<<< orphan*/  cxgb_offload_ctl ; 
 int /*<<< orphan*/  register_tdev (struct t3cdev*) ; 
 int /*<<< orphan*/  t3_offload_tx ; 

void cxgb3_adapter_ofld(struct adapter *adapter)
{
	struct t3cdev *tdev = &adapter->tdev;

	INIT_LIST_HEAD(&tdev->ofld_dev_list);

	cxgb3_set_dummy_ops(tdev);
	tdev->send = t3_offload_tx;
	tdev->ctl = cxgb_offload_ctl;
	tdev->type = adap2type(adapter);

	register_tdev(tdev);
}