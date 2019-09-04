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
struct qlcnic_npar_info {int /*<<< orphan*/  mac; int /*<<< orphan*/  max_bw; int /*<<< orphan*/  min_bw; int /*<<< orphan*/  phy_port; int /*<<< orphan*/  type; int /*<<< orphan*/  active; int /*<<< orphan*/  pci_func; } ;
struct qlcnic_hardware_context {int total_nic_func; int msix_supported; int /*<<< orphan*/  fw_hal_version; int /*<<< orphan*/  max_pci_func; } ;
struct qlcnic_adapter {int flags; struct qlcnic_npar_info* npars; TYPE_1__* pdev; struct qlcnic_hardware_context* ahw; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int EIO ; 
 int QLCNIC_ADAPTER_INITIALIZED ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  qlcnic_83xx_config_vnic_buff_descriptors (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_enable_vnic_mode (struct qlcnic_adapter*,int) ; 
 int /*<<< orphan*/  qlcnic_83xx_get_minidump_template (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_83xx_get_port_info (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_83xx_set_vnic_opmode (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_init_pci_info (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_reset_npar_config (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_set_default_offload_settings (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_use_msi_x ; 

__attribute__((used)) static int qlcnic_83xx_init_mgmt_vnic(struct qlcnic_adapter *adapter)
{
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	struct device *dev = &adapter->pdev->dev;
	struct qlcnic_npar_info *npar;
	int i, err = -EIO;

	qlcnic_83xx_get_minidump_template(adapter);

	if (!(adapter->flags & QLCNIC_ADAPTER_INITIALIZED)) {
		if (qlcnic_init_pci_info(adapter))
			return err;

		npar = adapter->npars;

		for (i = 0; i < ahw->total_nic_func; i++, npar++) {
			dev_info(dev, "id:%d active:%d type:%d port:%d min_bw:%d max_bw:%d mac_addr:%pM\n",
				 npar->pci_func, npar->active, npar->type,
				 npar->phy_port, npar->min_bw, npar->max_bw,
				 npar->mac);
		}

		dev_info(dev, "Max functions = %d, active functions = %d\n",
			 ahw->max_pci_func, ahw->total_nic_func);

		if (qlcnic_83xx_set_vnic_opmode(adapter))
			return err;

		if (qlcnic_set_default_offload_settings(adapter))
			return err;
	} else {
		if (qlcnic_reset_npar_config(adapter))
			return err;
	}

	if (qlcnic_83xx_get_port_info(adapter))
		return err;

	qlcnic_83xx_config_vnic_buff_descriptors(adapter);
	ahw->msix_supported = qlcnic_use_msi_x ? 1 : 0;
	adapter->flags |= QLCNIC_ADAPTER_INITIALIZED;
	qlcnic_83xx_enable_vnic_mode(adapter, 1);

	dev_info(dev, "HAL Version: %d, Management function\n",
		 ahw->fw_hal_version);

	return 0;
}