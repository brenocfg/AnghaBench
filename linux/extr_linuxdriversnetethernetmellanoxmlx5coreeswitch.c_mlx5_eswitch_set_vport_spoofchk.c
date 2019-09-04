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
struct TYPE_2__ {int spoofchk; int /*<<< orphan*/  mac; } ;
struct mlx5_vport {TYPE_1__ info; scalar_t__ enabled; int /*<<< orphan*/  vport; } ;
struct mlx5_eswitch {scalar_t__ mode; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  dev; struct mlx5_vport* vports; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  ESW_ALLOWED (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  LEGAL_VPORT (struct mlx5_eswitch*,int) ; 
 scalar_t__ SRIOV_LEGACY ; 
 int esw_vport_ingress_config (struct mlx5_eswitch*,struct mlx5_vport*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int mlx5_eswitch_set_vport_spoofchk(struct mlx5_eswitch *esw,
				    int vport, bool spoofchk)
{
	struct mlx5_vport *evport;
	bool pschk;
	int err = 0;

	if (!ESW_ALLOWED(esw))
		return -EPERM;
	if (!LEGAL_VPORT(esw, vport))
		return -EINVAL;

	mutex_lock(&esw->state_lock);
	evport = &esw->vports[vport];
	pschk = evport->info.spoofchk;
	evport->info.spoofchk = spoofchk;
	if (pschk && !is_valid_ether_addr(evport->info.mac))
		mlx5_core_warn(esw->dev,
			       "Spoofchk in set while MAC is invalid, vport(%d)\n",
			       evport->vport);
	if (evport->enabled && esw->mode == SRIOV_LEGACY)
		err = esw_vport_ingress_config(esw, evport);
	if (err)
		evport->info.spoofchk = pschk;
	mutex_unlock(&esw->state_lock);

	return err;
}