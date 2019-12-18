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
struct mlxsw_pci_queue {int dummy; } ;
struct mlxsw_pci {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_PCI_QUEUE_TYPE_SDQ ; 
 struct mlxsw_pci_queue* __mlxsw_pci_queue_get (struct mlxsw_pci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlxsw_pci_queue *mlxsw_pci_sdq_get(struct mlxsw_pci *mlxsw_pci,
						 u8 q_num)
{
	return __mlxsw_pci_queue_get(mlxsw_pci,
				     MLXSW_PCI_QUEUE_TYPE_SDQ, q_num);
}