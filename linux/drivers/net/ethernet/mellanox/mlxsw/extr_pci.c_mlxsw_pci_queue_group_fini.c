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
struct mlxsw_pci_queue_type_group {int count; int /*<<< orphan*/ * q; } ;
struct mlxsw_pci_queue_ops {int /*<<< orphan*/  type; } ;
struct mlxsw_pci {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_pci_queue_fini (struct mlxsw_pci*,struct mlxsw_pci_queue_ops const*,int /*<<< orphan*/ *) ; 
 struct mlxsw_pci_queue_type_group* mlxsw_pci_queue_type_group_get (struct mlxsw_pci*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_pci_queue_group_fini(struct mlxsw_pci *mlxsw_pci,
				       const struct mlxsw_pci_queue_ops *q_ops)
{
	struct mlxsw_pci_queue_type_group *queue_group;
	int i;

	queue_group = mlxsw_pci_queue_type_group_get(mlxsw_pci, q_ops->type);
	for (i = 0; i < queue_group->count; i++)
		mlxsw_pci_queue_fini(mlxsw_pci, q_ops, &queue_group->q[i]);
	kfree(queue_group->q);
}