#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* buf; } ;
struct mlxsw_pci_queue {TYPE_1__ mem_item; } ;

/* Variables and functions */

__attribute__((used)) static char *__mlxsw_pci_queue_elem_get(struct mlxsw_pci_queue *q,
					size_t elem_size, int elem_index)
{
	return q->mem_item.buf + (elem_size * elem_index);
}