#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct mlx4_vport_state {int spoofchk; int /*<<< orphan*/  mac; } ;
struct TYPE_7__ {TYPE_2__* vf_admin; } ;
struct TYPE_8__ {TYPE_3__ master; } ;
struct mlx4_priv {TYPE_4__ mfunc; } ;
struct TYPE_5__ {int flags2; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
struct TYPE_6__ {struct mlx4_vport_state* vport; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int EPROTONOSUPPORT ; 
 int ETH_ALEN ; 
 int MLX4_DEV_CAP_FLAG2_FSM ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ *) ; 
 int mlx4_get_slave_indx (struct mlx4_dev*,int) ; 
 int /*<<< orphan*/  mlx4_info (struct mlx4_dev*,char*) ; 
 int /*<<< orphan*/  mlx4_is_master (struct mlx4_dev*) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int mlx4_slaves_closest_port (struct mlx4_dev*,int,int) ; 
 int /*<<< orphan*/  mlx4_u64_to_mac (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int mlx4_set_vf_spoofchk(struct mlx4_dev *dev, int port, int vf, bool setting)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	struct mlx4_vport_state *s_info;
	int slave;
	u8 mac[ETH_ALEN];

	if ((!mlx4_is_master(dev)) ||
	    !(dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_FSM))
		return -EPROTONOSUPPORT;

	slave = mlx4_get_slave_indx(dev, vf);
	if (slave < 0)
		return -EINVAL;

	port = mlx4_slaves_closest_port(dev, slave, port);
	s_info = &priv->mfunc.master.vf_admin[slave].vport[port];

	mlx4_u64_to_mac(mac, s_info->mac);
	if (setting && !is_valid_ether_addr(mac)) {
		mlx4_info(dev, "Illegal MAC with spoofchk\n");
		return -EPERM;
	}

	s_info->spoofchk = setting;

	return 0;
}