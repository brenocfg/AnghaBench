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
struct mlxsw_pci_queue_elem_info {char* elem; } ;
struct mlxsw_pci_queue {int /*<<< orphan*/  consumer_counter; } ;

/* Variables and functions */
 scalar_t__ mlxsw_pci_elem_hw_owned (struct mlxsw_pci_queue*,int) ; 
 int mlxsw_pci_eqe_owner_get (char*) ; 
 struct mlxsw_pci_queue_elem_info* mlxsw_pci_queue_elem_info_consumer_get (struct mlxsw_pci_queue*) ; 
 int /*<<< orphan*/  rmb () ; 

__attribute__((used)) static char *mlxsw_pci_eq_sw_eqe_get(struct mlxsw_pci_queue *q)
{
	struct mlxsw_pci_queue_elem_info *elem_info;
	char *elem;
	bool owner_bit;

	elem_info = mlxsw_pci_queue_elem_info_consumer_get(q);
	elem = elem_info->elem;
	owner_bit = mlxsw_pci_eqe_owner_get(elem);
	if (mlxsw_pci_elem_hw_owned(q, owner_bit))
		return NULL;
	q->consumer_counter++;
	rmb(); /* make sure we read owned bit before the rest of elem */
	return elem;
}