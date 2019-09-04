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
typedef  size_t u8 ;
struct mlxsw_pci_queue {int dummy; } ;
struct mlxsw_pci {TYPE_1__* queues; } ;
typedef  enum mlxsw_pci_queue_type { ____Placeholder_mlxsw_pci_queue_type } mlxsw_pci_queue_type ;
struct TYPE_2__ {struct mlxsw_pci_queue* q; } ;

/* Variables and functions */

__attribute__((used)) static struct mlxsw_pci_queue *
__mlxsw_pci_queue_get(struct mlxsw_pci *mlxsw_pci,
		      enum mlxsw_pci_queue_type q_type, u8 q_num)
{
	return &mlxsw_pci->queues[q_type].q[q_num];
}