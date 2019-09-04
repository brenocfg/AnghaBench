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
typedef  int /*<<< orphan*/  u8 ;
struct mlx5_eswitch_rep {int vport; int /*<<< orphan*/  hw_id; } ;
struct mlx5_esw_offload {struct mlx5_eswitch_rep* vport_reps; } ;
struct mlx5_eswitch {struct mlx5_esw_offload offloads; struct mlx5_core_dev* dev; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ETH_ALEN ; 
 int FDB_UPLINK_VPORT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MLX5_TOTAL_VPORTS (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mlx5_eswitch_rep* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_query_nic_vport_mac_address (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int esw_offloads_init_reps(struct mlx5_eswitch *esw)
{
	int total_vfs = MLX5_TOTAL_VPORTS(esw->dev);
	struct mlx5_core_dev *dev = esw->dev;
	struct mlx5_esw_offload *offloads;
	struct mlx5_eswitch_rep *rep;
	u8 hw_id[ETH_ALEN];
	int vport;

	esw->offloads.vport_reps = kcalloc(total_vfs,
					   sizeof(struct mlx5_eswitch_rep),
					   GFP_KERNEL);
	if (!esw->offloads.vport_reps)
		return -ENOMEM;

	offloads = &esw->offloads;
	mlx5_query_nic_vport_mac_address(dev, 0, hw_id);

	for (vport = 0; vport < total_vfs; vport++) {
		rep = &offloads->vport_reps[vport];

		rep->vport = vport;
		ether_addr_copy(rep->hw_id, hw_id);
	}

	offloads->vport_reps[0].vport = FDB_UPLINK_VPORT;

	return 0;
}