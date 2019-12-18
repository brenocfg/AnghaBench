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
struct qlcnic_hardware_context {int num_msix; scalar_t__ pci_func; TYPE_2__* intr_tbl; } ;
struct qlcnic_adapter {int flags; TYPE_1__* pdev; struct qlcnic_hardware_context* ahw; void* drv_tx_rings; void* drv_sds_rings; } ;
struct TYPE_4__ {int id; scalar_t__ src; int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  QLCNIC_INTRPT_INTX ; 
 int /*<<< orphan*/  QLCNIC_INTRPT_MSIX ; 
 int QLCNIC_MSIX_ENABLED ; 
 void* QLCNIC_SINGLE_RING ; 
 int QLCNIC_TSS_RSS ; 
 scalar_t__ QLC_MAX_LEGACY_FUNC_SUPP ; 
 int /*<<< orphan*/  array_size (int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int qlcnic_83xx_calculate_msix_vector (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_enable_legacy (struct qlcnic_adapter*) ; 
 int qlcnic_enable_msix (struct qlcnic_adapter*,int) ; 
 int qlcnic_setup_tss_rss_intr (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_sriov_vf_check (struct qlcnic_adapter*) ; 
 TYPE_2__* vzalloc (int /*<<< orphan*/ ) ; 

int qlcnic_83xx_setup_intr(struct qlcnic_adapter *adapter)
{
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	int err, i, num_msix;

	if (adapter->flags & QLCNIC_TSS_RSS) {
		err = qlcnic_setup_tss_rss_intr(adapter);
		if (err < 0)
			return err;
		num_msix = ahw->num_msix;
	} else {
		num_msix = qlcnic_83xx_calculate_msix_vector(adapter);

		err = qlcnic_enable_msix(adapter, num_msix);
		if (err == -ENOMEM)
			return err;

		if (adapter->flags & QLCNIC_MSIX_ENABLED) {
			num_msix = ahw->num_msix;
		} else {
			if (qlcnic_sriov_vf_check(adapter))
				return -EINVAL;
			num_msix = 1;
			adapter->drv_sds_rings = QLCNIC_SINGLE_RING;
			adapter->drv_tx_rings = QLCNIC_SINGLE_RING;
		}
	}

	/* setup interrupt mapping table for fw */
	ahw->intr_tbl =
		vzalloc(array_size(num_msix,
				   sizeof(struct qlcnic_intrpt_config)));
	if (!ahw->intr_tbl)
		return -ENOMEM;

	if (!(adapter->flags & QLCNIC_MSIX_ENABLED)) {
		if (adapter->ahw->pci_func >= QLC_MAX_LEGACY_FUNC_SUPP) {
			dev_err(&adapter->pdev->dev, "PCI function number 8 and higher are not supported with legacy interrupt, func 0x%x\n",
				ahw->pci_func);
			return -EOPNOTSUPP;
		}

		qlcnic_83xx_enable_legacy(adapter);
	}

	for (i = 0; i < num_msix; i++) {
		if (adapter->flags & QLCNIC_MSIX_ENABLED)
			ahw->intr_tbl[i].type = QLCNIC_INTRPT_MSIX;
		else
			ahw->intr_tbl[i].type = QLCNIC_INTRPT_INTX;
		ahw->intr_tbl[i].id = i;
		ahw->intr_tbl[i].src = 0;
	}

	return 0;
}