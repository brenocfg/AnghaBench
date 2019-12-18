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
typedef  int /*<<< orphan*/  u8 ;
struct qlcnic_npar_info {int /*<<< orphan*/  dest_npar; scalar_t__ enable_pm; int /*<<< orphan*/  max_bw; int /*<<< orphan*/  min_bw; int /*<<< orphan*/  eswitch_status; int /*<<< orphan*/  pci_func; } ;
struct qlcnic_info {int /*<<< orphan*/  max_tx_bw; int /*<<< orphan*/  min_tx_bw; } ;
struct qlcnic_adapter {struct qlcnic_npar_info* npars; TYPE_1__* ahw; int /*<<< orphan*/  need_fw_reset; } ;
struct TYPE_2__ {int total_nic_func; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct qlcnic_info*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ qlcnic_82xx_check (struct qlcnic_adapter*) ; 
 int qlcnic_config_port_mirroring (struct qlcnic_adapter*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int qlcnic_get_nic_info (struct qlcnic_adapter*,struct qlcnic_info*,int /*<<< orphan*/ ) ; 
 int qlcnic_reset_eswitch_config (struct qlcnic_adapter*,struct qlcnic_npar_info*,int /*<<< orphan*/ ) ; 
 int qlcnic_set_nic_info (struct qlcnic_adapter*,struct qlcnic_info*) ; 

int qlcnic_reset_npar_config(struct qlcnic_adapter *adapter)
{
	int i, err;
	struct qlcnic_npar_info *npar;
	struct qlcnic_info nic_info;
	u8 pci_func;

	if (qlcnic_82xx_check(adapter))
		if (!adapter->need_fw_reset)
			return 0;

	/* Set the NPAR config data after FW reset */
	for (i = 0; i < adapter->ahw->total_nic_func; i++) {
		npar = &adapter->npars[i];
		pci_func = npar->pci_func;
		if (!adapter->npars[i].eswitch_status)
			continue;

		memset(&nic_info, 0, sizeof(struct qlcnic_info));
		err = qlcnic_get_nic_info(adapter, &nic_info, pci_func);
		if (err)
			return err;
		nic_info.min_tx_bw = npar->min_bw;
		nic_info.max_tx_bw = npar->max_bw;
		err = qlcnic_set_nic_info(adapter, &nic_info);
		if (err)
			return err;

		if (npar->enable_pm) {
			err = qlcnic_config_port_mirroring(adapter,
							   npar->dest_npar, 1,
							   pci_func);
			if (err)
				return err;
		}
		err = qlcnic_reset_eswitch_config(adapter, npar, pci_func);
		if (err)
			return err;
	}
	return 0;
}