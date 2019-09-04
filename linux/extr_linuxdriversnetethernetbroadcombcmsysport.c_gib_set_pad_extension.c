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
typedef  int u32 ;
struct bcm_sysport_priv {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int ENET_BRCM_TAG_LEN ; 
 int /*<<< orphan*/  GIB_CONTROL ; 
 int GIB_IPG_LEN_MASK ; 
 int GIB_IPG_LEN_SHIFT ; 
 int GIB_PAD_EXTENSION_MASK ; 
 int GIB_PAD_EXTENSION_SHIFT ; 
 int gib_readl (struct bcm_sysport_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gib_writel (struct bcm_sysport_priv*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ netdev_uses_dsa (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void gib_set_pad_extension(struct bcm_sysport_priv *priv)
{
	u32 reg;

	reg = gib_readl(priv, GIB_CONTROL);
	/* Include Broadcom tag in pad extension and fix up IPG_LENGTH */
	if (netdev_uses_dsa(priv->netdev)) {
		reg &= ~(GIB_PAD_EXTENSION_MASK << GIB_PAD_EXTENSION_SHIFT);
		reg |= ENET_BRCM_TAG_LEN << GIB_PAD_EXTENSION_SHIFT;
	}
	reg &= ~(GIB_IPG_LEN_MASK << GIB_IPG_LEN_SHIFT);
	reg |= 12 << GIB_IPG_LEN_SHIFT;
	gib_writel(priv, reg, GIB_CONTROL);
}