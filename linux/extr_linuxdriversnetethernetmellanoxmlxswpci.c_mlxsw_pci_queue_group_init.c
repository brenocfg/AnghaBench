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
typedef  int u8 ;
struct mlxsw_pci_queue_type_group {int count; int /*<<< orphan*/ * q; } ;
struct mlxsw_pci_queue_ops {int /*<<< orphan*/  type; } ;
struct mlxsw_pci {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_pci_queue_fini (struct mlxsw_pci*,struct mlxsw_pci_queue_ops const*,int /*<<< orphan*/ *) ; 
 int mlxsw_pci_queue_init (struct mlxsw_pci*,char*,struct mlxsw_pci_queue_ops const*,int /*<<< orphan*/ *,int) ; 
 struct mlxsw_pci_queue_type_group* mlxsw_pci_queue_type_group_get (struct mlxsw_pci*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_pci_queue_group_init(struct mlxsw_pci *mlxsw_pci, char *mbox,
				      const struct mlxsw_pci_queue_ops *q_ops,
				      u8 num_qs)
{
	struct mlxsw_pci_queue_type_group *queue_group;
	int i;
	int err;

	queue_group = mlxsw_pci_queue_type_group_get(mlxsw_pci, q_ops->type);
	queue_group->q = kcalloc(num_qs, sizeof(*queue_group->q), GFP_KERNEL);
	if (!queue_group->q)
		return -ENOMEM;

	for (i = 0; i < num_qs; i++) {
		err = mlxsw_pci_queue_init(mlxsw_pci, mbox, q_ops,
					   &queue_group->q[i], i);
		if (err)
			goto err_queue_init;
	}
	queue_group->count = num_qs;

	return 0;

err_queue_init:
	for (i--; i >= 0; i--)
		mlxsw_pci_queue_fini(mlxsw_pci, q_ops, &queue_group->q[i]);
	kfree(queue_group->q);
	return err;
}