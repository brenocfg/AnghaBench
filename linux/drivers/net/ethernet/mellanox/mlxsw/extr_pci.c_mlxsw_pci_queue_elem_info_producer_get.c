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
typedef  int u16 ;
struct mlxsw_pci_queue_elem_info {int dummy; } ;
struct mlxsw_pci_queue {int producer_counter; int count; int consumer_counter; } ;

/* Variables and functions */
 struct mlxsw_pci_queue_elem_info* mlxsw_pci_queue_elem_info_get (struct mlxsw_pci_queue*,int) ; 

__attribute__((used)) static struct mlxsw_pci_queue_elem_info *
mlxsw_pci_queue_elem_info_producer_get(struct mlxsw_pci_queue *q)
{
	int index = q->producer_counter & (q->count - 1);

	if ((u16) (q->producer_counter - q->consumer_counter) == q->count)
		return NULL;
	return mlxsw_pci_queue_elem_info_get(q, index);
}