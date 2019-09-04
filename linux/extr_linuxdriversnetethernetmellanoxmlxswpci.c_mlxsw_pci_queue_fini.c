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
struct mlxsw_pci_queue_ops {int /*<<< orphan*/  (* fini ) (struct mlxsw_pci*,struct mlxsw_pci_queue*) ;} ;
struct mlxsw_pci_mem_item {int /*<<< orphan*/  mapaddr; int /*<<< orphan*/  buf; int /*<<< orphan*/  size; } ;
struct mlxsw_pci_queue {int /*<<< orphan*/  elem_info; struct mlxsw_pci_mem_item mem_item; } ;
struct mlxsw_pci {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mlxsw_pci*,struct mlxsw_pci_queue*) ; 

__attribute__((used)) static void mlxsw_pci_queue_fini(struct mlxsw_pci *mlxsw_pci,
				 const struct mlxsw_pci_queue_ops *q_ops,
				 struct mlxsw_pci_queue *q)
{
	struct mlxsw_pci_mem_item *mem_item = &q->mem_item;

	q_ops->fini(mlxsw_pci, q);
	kfree(q->elem_info);
	pci_free_consistent(mlxsw_pci->pdev, mem_item->size,
			    mem_item->buf, mem_item->mapaddr);
}