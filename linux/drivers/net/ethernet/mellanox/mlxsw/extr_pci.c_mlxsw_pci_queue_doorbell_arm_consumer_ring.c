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
struct mlxsw_pci_queue {int /*<<< orphan*/  consumer_counter; } ;
struct mlxsw_pci {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mlxsw_pci_queue_doorbell_arm_set (struct mlxsw_pci*,struct mlxsw_pci_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void
mlxsw_pci_queue_doorbell_arm_consumer_ring(struct mlxsw_pci *mlxsw_pci,
					   struct mlxsw_pci_queue *q)
{
	wmb(); /* ensure all writes are done before we ring a bell */
	__mlxsw_pci_queue_doorbell_arm_set(mlxsw_pci, q, q->consumer_counter);
}