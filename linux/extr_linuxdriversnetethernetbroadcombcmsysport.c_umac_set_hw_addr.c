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
typedef  unsigned char u32 ;
struct bcm_sysport_priv {int /*<<< orphan*/  is_lite; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIB_MAC0 ; 
 int /*<<< orphan*/  GIB_MAC1 ; 
 int /*<<< orphan*/  UMAC_MAC0 ; 
 int /*<<< orphan*/  UMAC_MAC1 ; 
 int /*<<< orphan*/  gib_writel (struct bcm_sysport_priv*,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umac_writel (struct bcm_sysport_priv*,unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void umac_set_hw_addr(struct bcm_sysport_priv *priv,
			     unsigned char *addr)
{
	u32 mac0 = (addr[0] << 24) | (addr[1] << 16) | (addr[2] << 8) |
		    addr[3];
	u32 mac1 = (addr[4] << 8) | addr[5];

	if (!priv->is_lite) {
		umac_writel(priv, mac0, UMAC_MAC0);
		umac_writel(priv, mac1, UMAC_MAC1);
	} else {
		gib_writel(priv, mac0, GIB_MAC0);
		gib_writel(priv, mac1, GIB_MAC1);
	}
}