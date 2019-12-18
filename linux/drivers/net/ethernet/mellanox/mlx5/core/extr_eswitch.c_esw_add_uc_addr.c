#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_6__ {int /*<<< orphan*/ * addr; } ;
struct vport_addr {scalar_t__ vport; int mpfs; int /*<<< orphan*/  flow_rule; TYPE_3__ node; } ;
struct TYPE_4__ {scalar_t__ fdb; } ;
struct TYPE_5__ {TYPE_1__ legacy; } ;
struct mlx5_eswitch {scalar_t__ manager_vport; scalar_t__ mode; int /*<<< orphan*/  dev; TYPE_2__ fdb_table; } ;

/* Variables and functions */
 scalar_t__ MLX5_ESWITCH_LEGACY ; 
 int /*<<< orphan*/  esw_debug (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esw_fdb_set_vport_rule (struct mlx5_eswitch*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  esw_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int mlx5_mpfs_add_mac (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int esw_add_uc_addr(struct mlx5_eswitch *esw, struct vport_addr *vaddr)
{
	u8 *mac = vaddr->node.addr;
	u16 vport = vaddr->vport;
	int err;

	/* Skip mlx5_mpfs_add_mac for eswitch_managers,
	 * it is already done by its netdev in mlx5e_execute_l2_action
	 */
	if (esw->manager_vport == vport)
		goto fdb_add;

	err = mlx5_mpfs_add_mac(esw->dev, mac);
	if (err) {
		esw_warn(esw->dev,
			 "Failed to add L2 table mac(%pM) for vport(0x%x), err(%d)\n",
			 mac, vport, err);
		return err;
	}
	vaddr->mpfs = true;

fdb_add:
	/* SRIOV is enabled: Forward UC MAC to vport */
	if (esw->fdb_table.legacy.fdb && esw->mode == MLX5_ESWITCH_LEGACY)
		vaddr->flow_rule = esw_fdb_set_vport_rule(esw, mac, vport);

	esw_debug(esw->dev, "\tADDED UC MAC: vport[%d] %pM fr(%p)\n",
		  vport, mac, vaddr->flow_rule);

	return 0;
}