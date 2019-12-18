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
struct TYPE_5__ {int /*<<< orphan*/  peer_mutex; int /*<<< orphan*/  peer_flows; } ;
struct mlx5_eswitch {TYPE_3__* dev; TYPE_2__ offloads; } ;
struct mlx5_devcom {int dummy; } ;
struct TYPE_4__ {struct mlx5_devcom* devcom; } ;
struct TYPE_6__ {TYPE_1__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESW_OFFLOADS_DEVCOM_PAIR ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MLX5_CAP_ESW (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_DEVCOM_ESW_OFFLOADS ; 
 int /*<<< orphan*/  merged_eswitch ; 
 int /*<<< orphan*/  mlx5_devcom_register_component (struct mlx5_devcom*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  mlx5_devcom_send_event (struct mlx5_devcom*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  mlx5_esw_offloads_devcom_event ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void esw_offloads_devcom_init(struct mlx5_eswitch *esw)
{
	struct mlx5_devcom *devcom = esw->dev->priv.devcom;

	INIT_LIST_HEAD(&esw->offloads.peer_flows);
	mutex_init(&esw->offloads.peer_mutex);

	if (!MLX5_CAP_ESW(esw->dev, merged_eswitch))
		return;

	mlx5_devcom_register_component(devcom,
				       MLX5_DEVCOM_ESW_OFFLOADS,
				       mlx5_esw_offloads_devcom_event,
				       esw);

	mlx5_devcom_send_event(devcom,
			       MLX5_DEVCOM_ESW_OFFLOADS,
			       ESW_OFFLOADS_DEVCOM_PAIR, esw);
}