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
typedef  scalar_t__ u16 ;
struct TYPE_2__ {int /*<<< orphan*/  max_rate; int /*<<< orphan*/  min_rate; int /*<<< orphan*/  trusted; int /*<<< orphan*/  spoofchk; int /*<<< orphan*/  qos; int /*<<< orphan*/  vlan; int /*<<< orphan*/  link_state; int /*<<< orphan*/  mac; } ;
struct mlx5_vport {TYPE_1__ info; } ;
struct mlx5_eswitch {int /*<<< orphan*/  state_lock; } ;
struct ifla_vf_info {int /*<<< orphan*/  max_tx_rate; int /*<<< orphan*/  min_tx_rate; int /*<<< orphan*/  trusted; int /*<<< orphan*/  spoofchk; int /*<<< orphan*/  qos; int /*<<< orphan*/  vlan; int /*<<< orphan*/  linkstate; int /*<<< orphan*/  mac; scalar_t__ vf; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlx5_vport*) ; 
 int PTR_ERR (struct mlx5_vport*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ifla_vf_info*,int /*<<< orphan*/ ,int) ; 
 struct mlx5_vport* mlx5_eswitch_get_vport (struct mlx5_eswitch*,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int mlx5_eswitch_get_vport_config(struct mlx5_eswitch *esw,
				  u16 vport, struct ifla_vf_info *ivi)
{
	struct mlx5_vport *evport = mlx5_eswitch_get_vport(esw, vport);

	if (IS_ERR(evport))
		return PTR_ERR(evport);

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