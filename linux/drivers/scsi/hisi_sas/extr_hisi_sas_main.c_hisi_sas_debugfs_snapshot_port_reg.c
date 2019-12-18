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
typedef  scalar_t__ u32 ;
struct hisi_sas_debugfs_reg {int count; scalar_t__ (* read_port_reg ) (struct hisi_hba*,int,scalar_t__) ;scalar_t__ base_off; } ;
struct hisi_hba {int n_phy; scalar_t__* debugfs_port_reg; TYPE_1__* hw; } ;
struct TYPE_2__ {struct hisi_sas_debugfs_reg* debugfs_reg_port; } ;

/* Variables and functions */
 scalar_t__ stub1 (struct hisi_hba*,int,scalar_t__) ; 

__attribute__((used)) static void hisi_sas_debugfs_snapshot_port_reg(struct hisi_hba *hisi_hba)
{
	const struct hisi_sas_debugfs_reg *port =
		hisi_hba->hw->debugfs_reg_port;
	int i, phy_cnt;
	u32 offset;
	u32 *databuf;

	for (phy_cnt = 0; phy_cnt < hisi_hba->n_phy; phy_cnt++) {
		databuf = (u32 *)hisi_hba->debugfs_port_reg[phy_cnt];
		for (i = 0; i < port->count; i++, databuf++) {
			offset = port->base_off + 4 * i;
			*databuf = port->read_port_reg(hisi_hba, phy_cnt,
						       offset);
		}
	}
}