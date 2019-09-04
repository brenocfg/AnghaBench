#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qlcnic_intrpt_config {int dummy; } ;
struct qlcnic_hardware_context {int num_msix; TYPE_2__* intr_tbl; int /*<<< orphan*/  diag_test; } ;
struct qlcnic_adapter {int flags; TYPE_1__* pdev; struct qlcnic_hardware_context* ahw; } ;
struct TYPE_4__ {int id; scalar_t__ src; int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  QLCNIC_INTRPT_MSIX ; 
 int QLCNIC_MSIX_ENABLED ; 
 int /*<<< orphan*/  array_size (int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int qlcnic_82xx_config_intrpt (struct qlcnic_adapter*,int) ; 
 scalar_t__ qlcnic_check_multi_tx (struct qlcnic_adapter*) ; 
 TYPE_2__* vzalloc (int /*<<< orphan*/ ) ; 

int qlcnic_82xx_mq_intrpt(struct qlcnic_adapter *adapter, int op_type)
{
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	int err, i;

	if (qlcnic_check_multi_tx(adapter) &&
	    !ahw->diag_test &&
	    (adapter->flags & QLCNIC_MSIX_ENABLED)) {
		ahw->intr_tbl =
			vzalloc(array_size(sizeof(struct qlcnic_intrpt_config),
					   ahw->num_msix));
		if (!ahw->intr_tbl)
			return -ENOMEM;

		for (i = 0; i < ahw->num_msix; i++) {
			ahw->intr_tbl[i].type = QLCNIC_INTRPT_MSIX;
			ahw->intr_tbl[i].id = i;
			ahw->intr_tbl[i].src = 0;
		}

		err = qlcnic_82xx_config_intrpt(adapter, 1);
		if (err)
			dev_err(&adapter->pdev->dev,
				"Failed to configure Interrupt for %d vector\n",
				ahw->num_msix);
		return err;
	}

	return 0;
}