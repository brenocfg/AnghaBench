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
typedef  int /*<<< orphan*/  u8 ;
struct mlxsw_pci {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_PCI_QUEUE_TYPE_SDQ ; 
 int /*<<< orphan*/  __mlxsw_pci_queue_count (struct mlxsw_pci*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 mlxsw_pci_sdq_count(struct mlxsw_pci *mlxsw_pci)
{
	return __mlxsw_pci_queue_count(mlxsw_pci, MLXSW_PCI_QUEUE_TYPE_SDQ);
}