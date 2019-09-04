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
struct TYPE_2__ {int /*<<< orphan*/  max_rate; int /*<<< orphan*/  min_rate; int /*<<< orphan*/  trusted; int /*<<< orphan*/  spoofchk; int /*<<< orphan*/  qos; int /*<<< orphan*/  vlan; int /*<<< orphan*/  link_state; int /*<<< orphan*/  mac; } ;
struct mlx5_vport {TYPE_1__ info; } ;
struct mlx5_eswitch {int /*<<< orphan*/  state_lock; struct mlx5_vport* vports; int /*<<< orphan*/  dev; } ;
struct ifla_vf_info {int vf; int /*<<< orphan*/  max_tx_rate; int /*<<< orphan*/  min_tx_rate; int /*<<< orphan*/  trusted; int /*<<< orphan*/  spoofchk; int /*<<< orphan*/  qos; int /*<<< orphan*/  vlan; int /*<<< orphan*/  linkstate; int /*<<< orphan*/  mac; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  LEGAL_VPORT (struct mlx5_eswitch*,int) ; 
 int /*<<< orphan*/  MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ifla_vf_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vport_group_manager ; 

int mlx5_eswitch_get_vport_config(struct mlx5_eswitch *esw,
				  int vport, struct ifla_vf_info *ivi)
{
	struct mlx5_vport *evport;

	if (!esw || !MLX5_CAP_GEN(esw->dev, vport_group_manager))
		return -EPERM;
	if (!LEGAL_VPORT(esw, vport))
		return -EINVAL;

	evport = &esw->vports[vport];

	memset(ivi, 0, sizeof(*ivi));
	ivi->vf = vport - 1;

	mutex_lock(&esw->state_lock);
	ether_addr_copy(ivi->mac, evport->info.mac);
	ivi->linkstate = evport->info.link_state;
	ivi->vlan = evport->info.vlan;
	ivi->qos = evport->info.qos;
	ivi->spoofchk = evport->info.spoofchk;
	ivi->trusted = evport->info.trusted;
	ivi->min_tx_rate = evport->info.min_rate;
	ivi->max_tx_rate = evport->info.max_rate;
	mutex_unlock(&esw->state_lock);

	return 0;
}