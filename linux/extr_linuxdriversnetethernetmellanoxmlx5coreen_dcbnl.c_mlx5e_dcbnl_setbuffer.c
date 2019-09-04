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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct net_device {int /*<<< orphan*/  mtu; } ;
struct TYPE_4__ {int manual_buffer; } ;
struct mlx5e_priv {TYPE_2__ dcbx; struct mlx5_core_dev* mdev; } ;
struct mlx5e_port_buffer {TYPE_1__* buffer; } ;
struct mlx5_core_dev {int dummy; } ;
struct dcbnl_buffer {scalar_t__* buffer_size; scalar_t__* prio2buffer; } ;
struct TYPE_3__ {scalar_t__ size; } ;

/* Variables and functions */
 int DCBX_MAX_BUFFERS ; 
 int EOPNOTSUPP ; 
 int MLX5E_MAX_BUFFER ; 
 int MLX5E_MAX_PRIORITY ; 
 scalar_t__ MLX5E_PORT_BUFFER_PRIO2BUFFER ; 
 scalar_t__ MLX5E_PORT_BUFFER_SIZE ; 
 int /*<<< orphan*/  MLX5_BUFFER_SUPPORTED (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_core_dbg (struct mlx5_core_dev*,char*,int,scalar_t__) ; 
 int mlx5e_port_manual_buffer_config (struct mlx5e_priv*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 int mlx5e_port_query_buffer (struct mlx5e_priv*,struct mlx5e_port_buffer*) ; 
 int mlx5e_port_query_priority2buffer (struct mlx5_core_dev*,scalar_t__*) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlx5e_dcbnl_setbuffer(struct net_device *dev,
				 struct dcbnl_buffer *dcb_buffer)
{
	struct mlx5e_priv *priv = netdev_priv(dev);
	struct mlx5_core_dev *mdev = priv->mdev;
	struct mlx5e_port_buffer port_buffer;
	u8 old_prio2buffer[MLX5E_MAX_PRIORITY];
	u32 *buffer_size = NULL;
	u8 *prio2buffer = NULL;
	u32 changed = 0;
	int i, err;

	if (!MLX5_BUFFER_SUPPORTED(mdev))
		return -EOPNOTSUPP;

	for (i = 0; i < DCBX_MAX_BUFFERS; i++)
		mlx5_core_dbg(mdev, "buffer[%d]=%d\n", i, dcb_buffer->buffer_size[i]);

	for (i = 0; i < MLX5E_MAX_PRIORITY; i++)
		mlx5_core_dbg(mdev, "priority %d buffer%d\n", i, dcb_buffer->prio2buffer[i]);

	err = mlx5e_port_query_priority2buffer(mdev, old_prio2buffer);
	if (err)
		return err;

	for (i = 0; i < MLX5E_MAX_PRIORITY; i++) {
		if (dcb_buffer->prio2buffer[i] != old_prio2buffer[i]) {
			changed |= MLX5E_PORT_BUFFER_PRIO2BUFFER;
			prio2buffer = dcb_buffer->prio2buffer;
			break;
		}
	}

	err = mlx5e_port_query_buffer(priv, &port_buffer);
	if (err)
		return err;

	for (i = 0; i < MLX5E_MAX_BUFFER; i++) {
		if (port_buffer.buffer[i].size != dcb_buffer->buffer_size[i]) {
			changed |= MLX5E_PORT_BUFFER_SIZE;
			buffer_size = dcb_buffer->buffer_size;
			break;
		}
	}

	if (!changed)
		return 0;

	priv->dcbx.manual_buffer = true;
	err = mlx5e_port_manual_buffer_config(priv, changed, dev->mtu, NULL,
					      buffer_size, prio2buffer);
	return err;
}