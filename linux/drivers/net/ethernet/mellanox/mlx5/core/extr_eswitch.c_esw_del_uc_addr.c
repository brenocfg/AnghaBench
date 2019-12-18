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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {int /*<<< orphan*/ * addr; } ;
struct vport_addr {scalar_t__ vport; int mpfs; int /*<<< orphan*/ * flow_rule; TYPE_1__ node; } ;
struct mlx5_eswitch {scalar_t__ manager_vport; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  esw_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  mlx5_del_flow_rules (int /*<<< orphan*/ *) ; 
 int mlx5_mpfs_del_mac (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int esw_del_uc_addr(struct mlx5_eswitch *esw, struct vport_addr *vaddr)
{
	u8 *mac = vaddr->node.addr;
	u16 vport = vaddr->vport;
	int err = 0;

	/* Skip mlx5_mpfs_del_mac for eswitch managerss,
	 * it is already done by its netdev in mlx5e_execute_l2_action
	 */
	if (!vaddr->mpfs || esw->manager_vport == vport)
		goto fdb_del;

	err = mlx5_mpfs_del_mac(esw->dev, mac);
	if (err)
		esw_warn(esw->dev,
			 "Failed to del L2 table mac(%pM) for vport(%d), err(%d)\n",
			 mac, vport, err);
	vaddr->mpfs = false;

fdb_del:
	if (vaddr->flow_rule)
		mlx5_del_flow_rules(vaddr->flow_rule);
	vaddr->flow_rule = NULL;

	return 0;
}