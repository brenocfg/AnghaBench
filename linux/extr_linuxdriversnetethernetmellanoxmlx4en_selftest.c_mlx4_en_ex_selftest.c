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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct net_device {scalar_t__ mtu; } ;
struct mlx4_en_priv {scalar_t__ port_up; TYPE_3__* mdev; } ;
struct TYPE_6__ {TYPE_2__* dev; } ;
struct TYPE_4__ {int flags; } ;
struct TYPE_5__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int ETH_TEST_FL_FAILED ; 
 int ETH_TEST_FL_OFFLINE ; 
 int MLX4_DEV_CAP_FLAG_UC_LOOPBACK ; 
 int MLX4_EN_NUM_SELF_TEST ; 
 scalar_t__ MLX4_SELFTEST_LB_MIN_MTU ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mlx4_en_test_interrupts (struct mlx4_en_priv*) ; 
 scalar_t__ mlx4_en_test_link (struct mlx4_en_priv*) ; 
 scalar_t__ mlx4_en_test_loopback (struct mlx4_en_priv*) ; 
 scalar_t__ mlx4_en_test_registers (struct mlx4_en_priv*) ; 
 scalar_t__ mlx4_en_test_speed (struct mlx4_en_priv*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 

void mlx4_en_ex_selftest(struct net_device *dev, u32 *flags, u64 *buf)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	int i, carrier_ok;

	memset(buf, 0, sizeof(u64) * MLX4_EN_NUM_SELF_TEST);

	if (*flags & ETH_TEST_FL_OFFLINE) {
		/* disable the interface */
		carrier_ok = netif_carrier_ok(dev);

		netif_carrier_off(dev);
		/* Wait until all tx queues are empty.
		 * there should not be any additional incoming traffic
		 * since we turned the carrier off */
		msleep(200);

		if (priv->mdev->dev->caps.flags &
					MLX4_DEV_CAP_FLAG_UC_LOOPBACK) {
			buf[3] = mlx4_en_test_registers(priv);
			if (priv->port_up && dev->mtu >= MLX4_SELFTEST_LB_MIN_MTU)
				buf[4] = mlx4_en_test_loopback(priv);
		}

		if (carrier_ok)
			netif_carrier_on(dev);

	}
	buf[0] = mlx4_en_test_interrupts(priv);
	buf[1] = mlx4_en_test_link(priv);
	buf[2] = mlx4_en_test_speed(priv);

	for (i = 0; i < MLX4_EN_NUM_SELF_TEST; i++) {
		if (buf[i])
			*flags |= ETH_TEST_FL_FAILED;
	}
}