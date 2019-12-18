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
struct ethtool_wolinfo {int supported; int wolopts; int /*<<< orphan*/ * sopass; } ;
struct bcmgenet_priv {int wolopts; } ;

/* Variables and functions */
 int /*<<< orphan*/  UMAC_MPD_PW_LS ; 
 int /*<<< orphan*/  UMAC_MPD_PW_MS ; 
 int WAKE_MAGIC ; 
 int WAKE_MAGICSECURE ; 
 int /*<<< orphan*/  bcmgenet_umac_readl (struct bcmgenet_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct bcmgenet_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  put_unaligned_be16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unaligned_be32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void bcmgenet_get_wol(struct net_device *dev, struct ethtool_wolinfo *wol)
{
	struct bcmgenet_priv *priv = netdev_priv(dev);
	u32 reg;

	wol->supported = WAKE_MAGIC | WAKE_MAGICSECURE;
	wol->wolopts = priv->wolopts;
	memset(wol->sopass, 0, sizeof(wol->sopass));

	if (wol->wolopts & WAKE_MAGICSECURE) {
		reg = bcmgenet_umac_readl(priv, UMAC_MPD_PW_MS);
		put_unaligned_be16(reg, &wol->sopass[0]);
		reg = bcmgenet_umac_readl(priv, UMAC_MPD_PW_LS);
		put_unaligned_be32(reg, &wol->sopass[2]);
	}
}