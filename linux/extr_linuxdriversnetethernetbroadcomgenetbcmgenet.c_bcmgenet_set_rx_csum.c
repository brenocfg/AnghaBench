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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct bcmgenet_priv {int desc_rxchk_en; scalar_t__ crc_fwd_en; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int NETIF_F_RXCSUM ; 
 int /*<<< orphan*/  RBUF_CHK_CTRL ; 
 int /*<<< orphan*/  RBUF_RXCHK_EN ; 
 int /*<<< orphan*/  RBUF_SKIP_FCS ; 
 int /*<<< orphan*/  bcmgenet_rbuf_readl (struct bcmgenet_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcmgenet_rbuf_writel (struct bcmgenet_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bcmgenet_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bcmgenet_set_rx_csum(struct net_device *dev,
				netdev_features_t wanted)
{
	struct bcmgenet_priv *priv = netdev_priv(dev);
	u32 rbuf_chk_ctrl;
	bool rx_csum_en;

	rx_csum_en = !!(wanted & NETIF_F_RXCSUM);

	rbuf_chk_ctrl = bcmgenet_rbuf_readl(priv, RBUF_CHK_CTRL);

	/* enable rx checksumming */
	if (rx_csum_en)
		rbuf_chk_ctrl |= RBUF_RXCHK_EN;
	else
		rbuf_chk_ctrl &= ~RBUF_RXCHK_EN;
	priv->desc_rxchk_en = rx_csum_en;

	/* If UniMAC forwards CRC, we need to skip over it to get
	 * a valid CHK bit to be set in the per-packet status word
	*/
	if (rx_csum_en && priv->crc_fwd_en)
		rbuf_chk_ctrl |= RBUF_SKIP_FCS;
	else
		rbuf_chk_ctrl &= ~RBUF_SKIP_FCS;

	bcmgenet_rbuf_writel(priv, rbuf_chk_ctrl, RBUF_CHK_CTRL);

	return 0;
}