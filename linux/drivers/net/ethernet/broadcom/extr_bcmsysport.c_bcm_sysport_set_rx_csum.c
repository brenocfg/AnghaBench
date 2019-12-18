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
struct bcm_sysport_priv {int rx_chk_en; scalar_t__ crc_fwd; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int NETIF_F_RXCSUM ; 
 int /*<<< orphan*/  RXCHK_BRCM_TAG_EN ; 
 int /*<<< orphan*/  RXCHK_CONTROL ; 
 int /*<<< orphan*/  RXCHK_EN ; 
 int /*<<< orphan*/  RXCHK_L2_HDR_DIS ; 
 int /*<<< orphan*/  RXCHK_SKIP_FCS ; 
 struct bcm_sysport_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netdev_uses_dsa (struct net_device*) ; 
 int /*<<< orphan*/  rxchk_readl (struct bcm_sysport_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxchk_writel (struct bcm_sysport_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm_sysport_set_rx_csum(struct net_device *dev,
				    netdev_features_t wanted)
{
	struct bcm_sysport_priv *priv = netdev_priv(dev);
	u32 reg;

	priv->rx_chk_en = !!(wanted & NETIF_F_RXCSUM);
	reg = rxchk_readl(priv, RXCHK_CONTROL);
	/* Clear L2 header checks, which would prevent BPDUs
	 * from being received.
	 */
	reg &= ~RXCHK_L2_HDR_DIS;
	if (priv->rx_chk_en)
		reg |= RXCHK_EN;
	else
		reg &= ~RXCHK_EN;

	/* If UniMAC forwards CRC, we need to skip over it to get
	 * a valid CHK bit to be set in the per-packet status word
	 */
	if (priv->rx_chk_en && priv->crc_fwd)
		reg |= RXCHK_SKIP_FCS;
	else
		reg &= ~RXCHK_SKIP_FCS;

	/* If Broadcom tags are enabled (e.g: using a switch), make
	 * sure we tell the RXCHK hardware to expect a 4-bytes Broadcom
	 * tag after the Ethernet MAC Source Address.
	 */
	if (netdev_uses_dsa(dev))
		reg |= RXCHK_BRCM_TAG_EN;
	else
		reg &= ~RXCHK_BRCM_TAG_EN;

	rxchk_writel(priv, reg, RXCHK_CONTROL);
}