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
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_pci_queue {size_t type; int /*<<< orphan*/  num; } ;
struct mlxsw_pci {int /*<<< orphan*/  doorbell_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOORBELL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mlxsw_pci_doorbell_arm_type_offset ; 
 int /*<<< orphan*/  mlxsw_pci_write32 (struct mlxsw_pci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __mlxsw_pci_queue_doorbell_arm_set(struct mlxsw_pci *mlxsw_pci,
					       struct mlxsw_pci_queue *q,
					       u16 val)
{
	mlxsw_pci_write32(mlxsw_pci,
			  DOORBELL(mlxsw_pci->doorbell_offset,
				   mlxsw_pci_doorbell_arm_type_offset[q->type],
				   q->num), val);
}