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
struct net_device {int dummy; } ;
struct mlx5e_rep_priv {struct mlx5_eswitch_rep* rep; } ;
struct mlx5e_priv {struct mlx5e_rep_priv* ppriv; } ;
struct mlx5_eswitch_rep {int vport; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 int snprintf (char*,size_t,char*,int) ; 

__attribute__((used)) static int mlx5e_rep_get_phys_port_name(struct net_device *dev,
					char *buf, size_t len)
{
	struct mlx5e_priv *priv = netdev_priv(dev);
	struct mlx5e_rep_priv *rpriv = priv->ppriv;
	struct mlx5_eswitch_rep *rep = rpriv->rep;
	int ret;

	ret = snprintf(buf, len, "%d", rep->vport - 1);
	if (ret >= len)
		return -EOPNOTSUPP;

	return 0;
}