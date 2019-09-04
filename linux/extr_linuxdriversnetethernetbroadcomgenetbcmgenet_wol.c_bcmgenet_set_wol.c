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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct ethtool_wolinfo {int wolopts; int /*<<< orphan*/ * sopass; } ;
struct device {int dummy; } ;
struct bcmgenet_priv {int wol_irq_disabled; int wolopts; int /*<<< orphan*/  wol_irq; TYPE_1__* pdev; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  MPD_PW_EN ; 
 int /*<<< orphan*/  UMAC_MPD_CTRL ; 
 int /*<<< orphan*/  UMAC_MPD_PW_LS ; 
 int /*<<< orphan*/  UMAC_MPD_PW_MS ; 
 int WAKE_MAGIC ; 
 int WAKE_MAGICSECURE ; 
 int /*<<< orphan*/  bcmgenet_umac_readl (struct bcmgenet_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcmgenet_umac_writel (struct bcmgenet_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_can_wakeup (struct device*) ; 
 int /*<<< orphan*/  device_set_wakeup_enable (struct device*,int) ; 
 int /*<<< orphan*/  disable_irq_wake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq_wake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_unaligned_be16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_unaligned_be32 (int /*<<< orphan*/ *) ; 
 struct bcmgenet_priv* netdev_priv (struct net_device*) ; 

int bcmgenet_set_wol(struct net_device *dev, struct ethtool_wolinfo *wol)
{
	struct bcmgenet_priv *priv = netdev_priv(dev);
	struct device *kdev = &priv->pdev->dev;
	u32 reg;

	if (!device_can_wakeup(kdev))
		return -ENOTSUPP;

	if (wol->wolopts & ~(WAKE_MAGIC | WAKE_MAGICSECURE))
		return -EINVAL;

	reg = bcmgenet_umac_readl(priv, UMAC_MPD_CTRL);
	if (wol->wolopts & WAKE_MAGICSECURE) {
		bcmgenet_umac_writel(priv, get_unaligned_be16(&wol->sopass[0]),
				     UMAC_MPD_PW_MS);
		bcmgenet_umac_writel(priv, get_unaligned_be32(&wol->sopass[2]),
				     UMAC_MPD_PW_LS);
		reg |= MPD_PW_EN;
	} else {
		reg &= ~MPD_PW_EN;
	}
	bcmgenet_umac_writel(priv, reg, UMAC_MPD_CTRL);

	/* Flag the device and relevant IRQ as wakeup capable */
	if (wol->wolopts) {
		device_set_wakeup_enable(kdev, 1);
		/* Avoid unbalanced enable_irq_wake calls */
		if (priv->wol_irq_disabled)
			enable_irq_wake(priv->wol_irq);
		priv->wol_irq_disabled = false;
	} else {
		device_set_wakeup_enable(kdev, 0);
		/* Avoid unbalanced disable_irq_wake calls */
		if (!priv->wol_irq_disabled)
			disable_irq_wake(priv->wol_irq);
		priv->wol_irq_disabled = true;
	}

	priv->wolopts = wol->wolopts;

	return 0;
}