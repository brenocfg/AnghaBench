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
struct mlxsw_bus_info {int /*<<< orphan*/  psid; int /*<<< orphan*/  vsd; } ;
struct mlxsw_pci {int /*<<< orphan*/  core; struct mlxsw_bus_info bus_info; } ;

/* Variables and functions */
 int mlxsw_cmd_boardinfo (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_cmd_mbox_boardinfo_psid_memcpy_from (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_cmd_mbox_boardinfo_vsd_memcpy_from (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_cmd_mbox_zero (char*) ; 

__attribute__((used)) static int mlxsw_pci_boardinfo(struct mlxsw_pci *mlxsw_pci, char *mbox)
{
	struct mlxsw_bus_info *bus_info = &mlxsw_pci->bus_info;
	int err;

	mlxsw_cmd_mbox_zero(mbox);
	err = mlxsw_cmd_boardinfo(mlxsw_pci->core, mbox);
	if (err)
		return err;
	mlxsw_cmd_mbox_boardinfo_vsd_memcpy_from(mbox, bus_info->vsd);
	mlxsw_cmd_mbox_boardinfo_psid_memcpy_from(mbox, bus_info->psid);
	return 0;
}