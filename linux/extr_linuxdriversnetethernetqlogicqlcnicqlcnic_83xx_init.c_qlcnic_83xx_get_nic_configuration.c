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
typedef  scalar_t__ u8 ;
struct qlcnic_info {int capabilities; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  max_mac_filters; int /*<<< orphan*/  max_rx_ques; int /*<<< orphan*/  max_tx_ques; int /*<<< orphan*/  switch_mode; scalar_t__ phys_port; } ;
struct qlcnic_hardware_context {int capabilities; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  max_mac_filters; int /*<<< orphan*/  max_rx_ques; int /*<<< orphan*/  max_tx_ques; int /*<<< orphan*/  switch_mode; scalar_t__ physical_port; int /*<<< orphan*/  pci_func; } ;
struct qlcnic_adapter {int /*<<< orphan*/  state; struct qlcnic_hardware_context* ahw; } ;

/* Variables and functions */
 int EIO ; 
 int QLCNIC_VNIC_MODE ; 
 int QLC_83XX_DEFAULT_OPMODE ; 
 int QLC_83XX_ESWITCH_CAPABILITY ; 
 int /*<<< orphan*/  __QLCNIC_SRIOV_CAPABLE ; 
 int /*<<< orphan*/  memset (struct qlcnic_info*,int /*<<< orphan*/ ,int) ; 
 int qlcnic_get_nic_info (struct qlcnic_adapter*,struct qlcnic_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qlcnic_83xx_get_nic_configuration(struct qlcnic_adapter *adapter)
{
	int err;
	struct qlcnic_info nic_info;
	struct qlcnic_hardware_context *ahw = adapter->ahw;

	memset(&nic_info, 0, sizeof(struct qlcnic_info));
	err = qlcnic_get_nic_info(adapter, &nic_info, ahw->pci_func);
	if (err)
		return -EIO;

	ahw->physical_port = (u8) nic_info.phys_port;
	ahw->switch_mode = nic_info.switch_mode;
	ahw->max_tx_ques = nic_info.max_tx_ques;
	ahw->max_rx_ques = nic_info.max_rx_ques;
	ahw->capabilities = nic_info.capabilities;
	ahw->max_mac_filters = nic_info.max_mac_filters;
	ahw->max_mtu = nic_info.max_mtu;

	/* eSwitch capability indicates vNIC mode.
	 * vNIC and SRIOV are mutually exclusive operational modes.
	 * If SR-IOV capability is detected, SR-IOV physical function
	 * will get initialized in default mode.
	 * SR-IOV virtual function initialization follows a
	 * different code path and opmode.
	 * SRIOV mode has precedence over vNIC mode.
	 */
	if (test_bit(__QLCNIC_SRIOV_CAPABLE, &adapter->state))
		return QLC_83XX_DEFAULT_OPMODE;

	if (ahw->capabilities & QLC_83XX_ESWITCH_CAPABILITY)
		return QLCNIC_VNIC_MODE;

	return QLC_83XX_DEFAULT_OPMODE;
}