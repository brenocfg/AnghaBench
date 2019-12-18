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
struct qlcnic_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_BC_CMD_CHANNEL_TERM ; 
 int /*<<< orphan*/  __qlcnic_sriov_cleanup (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_sriov_cfg_bc_intr (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_sriov_channel_cfg_cmd (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qlcnic_sriov_vf_cleanup(struct qlcnic_adapter *adapter)
{
	qlcnic_sriov_channel_cfg_cmd(adapter, QLCNIC_BC_CMD_CHANNEL_TERM);
	qlcnic_sriov_cfg_bc_intr(adapter, 0);
	__qlcnic_sriov_cleanup(adapter);
}