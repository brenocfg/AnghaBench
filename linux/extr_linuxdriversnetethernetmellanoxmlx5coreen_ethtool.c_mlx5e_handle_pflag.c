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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int pflags; } ;
struct TYPE_3__ {TYPE_2__ params; } ;
struct mlx5e_priv {TYPE_1__ channels; } ;
typedef  int (* mlx5e_pflag_handler ) (struct net_device*,int) ;
typedef  enum mlx5e_priv_flag { ____Placeholder_mlx5e_priv_flag } mlx5e_priv_flag ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_SET_PFLAG (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,char*,int,int) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlx5e_handle_pflag(struct net_device *netdev,
			      u32 wanted_flags,
			      enum mlx5e_priv_flag flag,
			      mlx5e_pflag_handler pflag_handler)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);
	bool enable = !!(wanted_flags & flag);
	u32 changes = wanted_flags ^ priv->channels.params.pflags;
	int err;

	if (!(changes & flag))
		return 0;

	err = pflag_handler(netdev, enable);
	if (err) {
		netdev_err(netdev, "%s private flag 0x%x failed err %d\n",
			   enable ? "Enable" : "Disable", flag, err);
		return err;
	}

	MLX5E_SET_PFLAG(&priv->channels.params, flag, enable);
	return 0;
}