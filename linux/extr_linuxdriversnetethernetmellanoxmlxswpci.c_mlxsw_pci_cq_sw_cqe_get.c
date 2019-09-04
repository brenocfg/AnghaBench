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
struct mlxsw_pci_queue_elem_info {char* elem; } ;
struct TYPE_3__ {int /*<<< orphan*/  v; } ;
struct TYPE_4__ {TYPE_1__ cq; } ;
struct mlxsw_pci_queue {int /*<<< orphan*/  consumer_counter; TYPE_2__ u; } ;

/* Variables and functions */
 int mlxsw_pci_cqe_owner_get (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mlxsw_pci_elem_hw_owned (struct mlxsw_pci_queue*,int) ; 
 struct mlxsw_pci_queue_elem_info* mlxsw_pci_queue_elem_info_consumer_get (struct mlxsw_pci_queue*) ; 
 int /*<<< orphan*/  rmb () ; 

__attribute__((used)) static char *mlxsw_pci_cq_sw_cqe_get(struct mlxsw_pci_queue *q)
{
	struct mlxsw_pci_queue_elem_info *elem_info;
	char *elem;
	bool owner_bit;

	elem_info = mlxsw_pci_queue_elem_info_consumer_get(q);
	elem = elem_info->elem;
	owner_bit = mlxsw_pci_cqe_owner_get(q->u.cq.v, elem);
	if (mlxsw_pci_elem_hw_owned(q, owner_bit))
		return NULL;
	q->consumer_counter++;
	rmb(); /* make sure we read owned bit before the rest of elem */
	return elem;
}