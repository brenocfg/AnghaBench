#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {scalar_t__ v; } ;
struct TYPE_4__ {TYPE_1__ cq; } ;
struct mlxsw_pci_queue {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_PCI_CQE01_SIZE ; 
 int /*<<< orphan*/  MLXSW_PCI_CQE2_SIZE ; 
 scalar_t__ MLXSW_PCI_CQE_V2 ; 

__attribute__((used)) static u8 mlxsw_pci_cq_elem_size(const struct mlxsw_pci_queue *q)
{
	return q->u.cq.v == MLXSW_PCI_CQE_V2 ? MLXSW_PCI_CQE2_SIZE :
					       MLXSW_PCI_CQE01_SIZE;
}