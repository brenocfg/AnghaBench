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
struct mlxsw_pci_queue {int /*<<< orphan*/  num; } ;
struct mlxsw_pci {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_cmd_hw2sw_cq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_pci_cq_fini(struct mlxsw_pci *mlxsw_pci,
			      struct mlxsw_pci_queue *q)
{
	mlxsw_cmd_hw2sw_cq(mlxsw_pci->core, q->num);
}