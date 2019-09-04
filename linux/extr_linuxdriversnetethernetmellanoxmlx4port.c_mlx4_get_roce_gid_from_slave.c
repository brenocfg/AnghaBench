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
typedef  int /*<<< orphan*/  u8 ;
struct mlx4_priv {TYPE_3__* port; } ;
struct mlx4_dev {int dummy; } ;
struct TYPE_5__ {TYPE_1__* roce_gids; } ;
struct TYPE_6__ {TYPE_2__ gid_table; } ;
struct TYPE_4__ {int /*<<< orphan*/  raw; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MLX4_ROCE_GID_ENTRY_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_is_master (struct mlx4_dev*) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 

int mlx4_get_roce_gid_from_slave(struct mlx4_dev *dev, int port, int slave_id,
				 u8 *gid)
{
	struct mlx4_priv *priv = mlx4_priv(dev);

	if (!mlx4_is_master(dev))
		return -EINVAL;

	memcpy(gid, priv->port[port].gid_table.roce_gids[slave_id].raw,
	       MLX4_ROCE_GID_ENTRY_SIZE);
	return 0;
}