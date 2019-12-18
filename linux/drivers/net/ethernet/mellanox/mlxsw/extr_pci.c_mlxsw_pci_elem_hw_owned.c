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
struct mlxsw_pci_queue {int consumer_counter; int count; } ;

/* Variables and functions */

__attribute__((used)) static bool mlxsw_pci_elem_hw_owned(struct mlxsw_pci_queue *q, bool owner_bit)
{
	return owner_bit != !!(q->consumer_counter & q->count);
}