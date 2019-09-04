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
struct net_device {int dummy; } ;
struct TYPE_2__ {int* dcb_pfc; scalar_t__ pfc_state; } ;
struct mlx4_en_priv {int dcbx_cap; scalar_t__ rx_skb_size; int /*<<< orphan*/  port; TYPE_1__ cee_config; struct mlx4_en_dev* mdev; struct mlx4_en_port_profile* prof; } ;
struct mlx4_en_port_profile {int rx_ppp; int tx_ppp; int rx_pause; int tx_pause; } ;
struct mlx4_en_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CEE_DCBX_MAX_PRIO ; 
 int DCB_CAP_DCBX_VER_CEE ; 
 scalar_t__ ETH_FCS_LEN ; 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*) ; 
 scalar_t__ mlx4_SET_PORT_general (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int,int,int) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 
#define  pfc_disabled 131 
#define  pfc_enabled_full 130 
#define  pfc_enabled_rx 129 
#define  pfc_enabled_tx 128 

__attribute__((used)) static u8 mlx4_en_dcbnl_set_all(struct net_device *netdev)
{
	struct mlx4_en_priv *priv = netdev_priv(netdev);
	struct mlx4_en_port_profile *prof = priv->prof;
	struct mlx4_en_dev *mdev = priv->mdev;
	u8 tx_pause, tx_ppp, rx_pause, rx_ppp;

	if (!(priv->dcbx_cap & DCB_CAP_DCBX_VER_CEE))
		return 1;

	if (priv->cee_config.pfc_state) {
		int tc;
		rx_ppp = prof->rx_ppp;
		tx_ppp = prof->tx_ppp;

		for (tc = 0; tc < CEE_DCBX_MAX_PRIO; tc++) {
			u8 tc_mask = 1 << tc;

			switch (priv->cee_config.dcb_pfc[tc]) {
			case pfc_disabled:
				tx_ppp &= ~tc_mask;
				rx_ppp &= ~tc_mask;
				break;
			case pfc_enabled_full:
				tx_ppp |= tc_mask;
				rx_ppp |= tc_mask;
				break;
			case pfc_enabled_tx:
				tx_ppp |= tc_mask;
				rx_ppp &= ~tc_mask;
				break;
			case pfc_enabled_rx:
				tx_ppp &= ~tc_mask;
				rx_ppp |= tc_mask;
				break;
			default:
				break;
			}
		}
		rx_pause = !!(rx_ppp || tx_ppp) ? 0 : prof->rx_pause;
		tx_pause = !!(rx_ppp || tx_ppp) ? 0 : prof->tx_pause;
	} else {
		rx_ppp = 0;
		tx_ppp = 0;
		rx_pause = prof->rx_pause;
		tx_pause = prof->tx_pause;
	}

	if (mlx4_SET_PORT_general(mdev->dev, priv->port,
				  priv->rx_skb_size + ETH_FCS_LEN,
				  tx_pause, tx_ppp, rx_pause, rx_ppp)) {
		en_err(priv, "Failed setting pause params\n");
		return 1;
	}

	prof->tx_ppp = tx_ppp;
	prof->rx_ppp = rx_ppp;
	prof->tx_pause = tx_pause;
	prof->rx_pause = rx_pause;

	return 0;
}