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
struct TYPE_3__ {scalar_t__ v; } ;
struct TYPE_4__ {TYPE_1__ cq; } ;
struct mlxsw_pci_queue {scalar_t__ num; TYPE_2__ u; } ;
struct mlxsw_pci {scalar_t__ max_cqe_ver; scalar_t__ num_sdq_cqs; } ;

/* Variables and functions */
 scalar_t__ MLXSW_PCI_CQE_V1 ; 
 scalar_t__ MLXSW_PCI_CQE_V2 ; 

__attribute__((used)) static void mlxsw_pci_cq_pre_init(struct mlxsw_pci *mlxsw_pci,
				  struct mlxsw_pci_queue *q)
{
	q->u.cq.v = mlxsw_pci->max_cqe_ver;

	/* For SDQ it is pointless to use CQEv2, so use CQEv1 instead */
	if (q->u.cq.v == MLXSW_PCI_CQE_V2 &&
	    q->num < mlxsw_pci->num_sdq_cqs)
		q->u.cq.v = MLXSW_PCI_CQE_V1;
}