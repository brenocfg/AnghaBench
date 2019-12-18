#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlx5_eswitch {TYPE_2__* dev; } ;
struct mlx5_devcom {int dummy; } ;
struct TYPE_3__ {struct mlx5_devcom* devcom; } ;
struct TYPE_4__ {TYPE_1__ priv; } ;

/* Variables and functions */
#define  ESW_OFFLOADS_DEVCOM_PAIR 129 
#define  ESW_OFFLOADS_DEVCOM_UNPAIR 128 
 int /*<<< orphan*/  MLX5_DEVCOM_ESW_OFFLOADS ; 
 int /*<<< orphan*/  mlx5_core_err (TYPE_2__*,char*,int,int) ; 
 int /*<<< orphan*/  mlx5_devcom_is_paired (struct mlx5_devcom*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_devcom_set_paired (struct mlx5_devcom*,int /*<<< orphan*/ ,int) ; 
 int mlx5_esw_offloads_pair (struct mlx5_eswitch*,struct mlx5_eswitch*) ; 
 int mlx5_esw_offloads_set_ns_peer (struct mlx5_eswitch*,struct mlx5_eswitch*,int) ; 
 int /*<<< orphan*/  mlx5_esw_offloads_unpair (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  mlx5_eswitch_vport_match_metadata_enabled (struct mlx5_eswitch*) ; 

__attribute__((used)) static int mlx5_esw_offloads_devcom_event(int event,
					  void *my_data,
					  void *event_data)
{
	struct mlx5_eswitch *esw = my_data;
	struct mlx5_devcom *devcom = esw->dev->priv.devcom;
	struct mlx5_eswitch *peer_esw = event_data;
	int err;

	switch (event) {
	case ESW_OFFLOADS_DEVCOM_PAIR:
		if (mlx5_eswitch_vport_match_metadata_enabled(esw) !=
		    mlx5_eswitch_vport_match_metadata_enabled(peer_esw))
			break;

		err = mlx5_esw_offloads_set_ns_peer(esw, peer_esw, true);
		if (err)
			goto err_out;
		err = mlx5_esw_offloads_pair(esw, peer_esw);
		if (err)
			goto err_peer;

		err = mlx5_esw_offloads_pair(peer_esw, esw);
		if (err)
			goto err_pair;

		mlx5_devcom_set_paired(devcom, MLX5_DEVCOM_ESW_OFFLOADS, true);
		break;

	case ESW_OFFLOADS_DEVCOM_UNPAIR:
		if (!mlx5_devcom_is_paired(devcom, MLX5_DEVCOM_ESW_OFFLOADS))
			break;

		mlx5_devcom_set_paired(devcom, MLX5_DEVCOM_ESW_OFFLOADS, false);
		mlx5_esw_offloads_unpair(peer_esw);
		mlx5_esw_offloads_unpair(esw);
		mlx5_esw_offloads_set_ns_peer(esw, peer_esw, false);
		break;
	}

	return 0;

err_pair:
	mlx5_esw_offloads_unpair(esw);
err_peer:
	mlx5_esw_offloads_set_ns_peer(esw, peer_esw, false);
err_out:
	mlx5_core_err(esw->dev, "esw offloads devcom event failure, event %u err %d",
		      event, err);
	return err;
}