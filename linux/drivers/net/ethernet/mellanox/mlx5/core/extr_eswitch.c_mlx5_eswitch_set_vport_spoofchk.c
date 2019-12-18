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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int spoofchk; int /*<<< orphan*/  mac; } ;
struct mlx5_vport {TYPE_1__ info; scalar_t__ enabled; int /*<<< orphan*/  vport; } ;
struct mlx5_eswitch {scalar_t__ mode; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  ESW_ALLOWED (struct mlx5_eswitch*) ; 
 scalar_t__ IS_ERR (struct mlx5_vport*) ; 
 scalar_t__ MLX5_ESWITCH_LEGACY ; 
 int PTR_ERR (struct mlx5_vport*) ; 
 int esw_vport_ingress_config (struct mlx5_eswitch*,struct mlx5_vport*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct mlx5_vport* mlx5_eswitch_get_vport (struct mlx5_eswitch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int mlx5_eswitch_set_vport_spoofchk(struct mlx5_eswitch *esw,
				    u16 vport, bool spoofchk)
{
	struct mlx5_vport *evport = mlx5_eswitch_get_vport(esw, vport);
	bool pschk;
	int err = 0;

	if (!ESW_ALLOWED(esw))
		return -EPERM;
	if (IS_ERR(evport))
		return PTR_ERR(evport);

	mutex_lock(&esw->state_lock);
	pschk = evport->info.spoofchk;
	evport->info.spoofchk = spoofchk;
	if (pschk && !is_valid_ether_addr(evport->info.mac))
		mlx5_core_warn(esw->dev,
			       "Spoofchk in set while MAC is invalid, vport(%d)\n",
			       evport->vport);
	if (evport->enabled && esw->mode == MLX5_ESWITCH_LEGACY)
		err = esw_vport_ingress_config(esw, evport);
	if (err)
		evport->info.spoofchk = pschk;
	mutex_unlock(&esw->state_lock);

	return err;
}