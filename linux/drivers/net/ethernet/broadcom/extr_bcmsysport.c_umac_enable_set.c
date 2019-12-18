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
struct bcm_sysport_priv {int /*<<< orphan*/  is_lite; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIB_CONTROL ; 
 int /*<<< orphan*/  UMAC_CMD ; 
 int /*<<< orphan*/  gib_readl (struct bcm_sysport_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gib_writel (struct bcm_sysport_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umac_readl (struct bcm_sysport_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umac_writel (struct bcm_sysport_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static inline void umac_enable_set(struct bcm_sysport_priv *priv,
				   u32 mask, unsigned int enable)
{
	u32 reg;

	if (!priv->is_lite) {
		reg = umac_readl(priv, UMAC_CMD);
		if (enable)
			reg |= mask;
		else
			reg &= ~mask;
		umac_writel(priv, reg, UMAC_CMD);
	} else {
		reg = gib_readl(priv, GIB_CONTROL);
		if (enable)
			reg |= mask;
		else
			reg &= ~mask;
		gib_writel(priv, reg, GIB_CONTROL);
	}

	/* UniMAC stops on a packet boundary, wait for a full-sized packet
	 * to be processed (1 msec).
	 */
	if (enable == 0)
		usleep_range(1000, 2000);
}