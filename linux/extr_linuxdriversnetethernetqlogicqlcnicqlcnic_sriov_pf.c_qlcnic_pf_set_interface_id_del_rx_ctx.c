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
typedef  int u32 ;
typedef  int u16 ;
struct qlcnic_adapter {TYPE_1__* ahw; } ;
struct TYPE_2__ {int /*<<< orphan*/  pci_func; } ;

/* Variables and functions */
 int qlcnic_sriov_pf_get_vport_handle (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 

void qlcnic_pf_set_interface_id_del_rx_ctx(struct qlcnic_adapter *adapter,
					   u32 *int_id)
{
	u16 vpid;

	vpid = qlcnic_sriov_pf_get_vport_handle(adapter,
						adapter->ahw->pci_func);
	*int_id |= vpid << 16;
}