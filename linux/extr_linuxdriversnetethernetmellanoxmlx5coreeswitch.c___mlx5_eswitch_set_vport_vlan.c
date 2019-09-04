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
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_2__ {int vlan; int qos; } ;
struct mlx5_vport {scalar_t__ enabled; TYPE_1__ info; } ;
struct mlx5_eswitch {scalar_t__ mode; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  dev; struct mlx5_vport* vports; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  ESW_ALLOWED (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  LEGAL_VPORT (struct mlx5_eswitch*,int) ; 
 scalar_t__ SRIOV_LEGACY ; 
 int esw_vport_egress_config (struct mlx5_eswitch*,struct mlx5_vport*) ; 
 int esw_vport_ingress_config (struct mlx5_eswitch*,struct mlx5_vport*) ; 
 int modify_esw_vport_cvlan (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int __mlx5_eswitch_set_vport_vlan(struct mlx5_eswitch *esw,
				  int vport, u16 vlan, u8 qos, u8 set_flags)
{
	struct mlx5_vport *evport;
	int err = 0;

	if (!ESW_ALLOWED(esw))
		return -EPERM;
	if (!LEGAL_VPORT(esw, vport) || (vlan > 4095) || (qos > 7))
		return -EINVAL;

	mutex_lock(&esw->state_lock);
	evport = &esw->vports[vport];

	err = modify_esw_vport_cvlan(esw->dev, vport, vlan, qos, set_flags);
	if (err)
		goto unlock;

	evport->info.vlan = vlan;
	evport->info.qos = qos;
	if (evport->enabled && esw->mode == SRIOV_LEGACY) {
		err = esw_vport_ingress_config(esw, evport);
		if (err)
			goto unlock;
		err = esw_vport_egress_config(esw, evport);
	}

unlock:
	mutex_unlock(&esw->state_lock);
	return err;
}