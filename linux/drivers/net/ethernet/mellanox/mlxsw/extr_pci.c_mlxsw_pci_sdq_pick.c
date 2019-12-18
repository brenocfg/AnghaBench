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
typedef  int u8 ;
struct mlxsw_tx_info {int local_port; } ;
struct mlxsw_pci_queue {int dummy; } ;
struct mlxsw_pci {int dummy; } ;

/* Variables and functions */
 int mlxsw_pci_sdq_count (struct mlxsw_pci*) ; 
 struct mlxsw_pci_queue* mlxsw_pci_sdq_get (struct mlxsw_pci*,int) ; 

__attribute__((used)) static struct mlxsw_pci_queue *
mlxsw_pci_sdq_pick(struct mlxsw_pci *mlxsw_pci,
		   const struct mlxsw_tx_info *tx_info)
{
	u8 sdqn = tx_info->local_port % mlxsw_pci_sdq_count(mlxsw_pci);

	return mlxsw_pci_sdq_get(mlxsw_pci, sdqn);
}