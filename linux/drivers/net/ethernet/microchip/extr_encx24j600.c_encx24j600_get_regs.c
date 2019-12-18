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
typedef  scalar_t__ u8 ;
typedef  unsigned int u16 ;
struct net_device {int dummy; } ;
struct ethtool_regs {int version; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;
struct encx24j600_priv {int /*<<< orphan*/  lock; TYPE_1__ ctx; } ;

/* Variables and functions */
 scalar_t__ SFR_REG_COUNT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct encx24j600_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,scalar_t__,unsigned int*) ; 

__attribute__((used)) static void encx24j600_get_regs(struct net_device *dev,
				struct ethtool_regs *regs, void *p)
{
	struct encx24j600_priv *priv = netdev_priv(dev);
	u16 *buff = p;
	u8 reg;

	regs->version = 1;
	mutex_lock(&priv->lock);
	for (reg = 0; reg < SFR_REG_COUNT; reg += 2) {
		unsigned int val = 0;
		/* ignore errors for unreadable registers */
		regmap_read(priv->ctx.regmap, reg, &val);
		buff[reg] = val & 0xffff;
	}
	mutex_unlock(&priv->lock);
}