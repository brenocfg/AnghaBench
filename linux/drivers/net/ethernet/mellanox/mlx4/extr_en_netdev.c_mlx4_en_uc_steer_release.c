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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct mlx4_qp {int qpn; } ;
struct mlx4_en_priv {int /*<<< orphan*/  port; struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {struct mlx4_dev* dev; } ;
struct TYPE_2__ {int steering_mode; } ;
struct mlx4_dev {TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  MLX4_PROT_ETH ; 
#define  MLX4_STEERING_MODE_B0 129 
#define  MLX4_STEERING_MODE_DEVICE_MANAGED 128 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_flow_detach (struct mlx4_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_unicast_detach (struct mlx4_dev*,struct mlx4_qp*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx4_en_uc_steer_release(struct mlx4_en_priv *priv,
				     unsigned char *mac, int qpn, u64 reg_id)
{
	struct mlx4_en_dev *mdev = priv->mdev;
	struct mlx4_dev *dev = mdev->dev;

	switch (dev->caps.steering_mode) {
	case MLX4_STEERING_MODE_B0: {
		struct mlx4_qp qp;
		u8 gid[16] = {0};

		qp.qpn = qpn;
		memcpy(&gid[10], mac, ETH_ALEN);
		gid[5] = priv->port;

		mlx4_unicast_detach(dev, &qp, gid, MLX4_PROT_ETH);
		break;
	}
	case MLX4_STEERING_MODE_DEVICE_MANAGED: {
		mlx4_flow_detach(dev, reg_id);
		break;
	}
	default:
		en_err(priv, "Invalid steering mode.\n");
	}
}