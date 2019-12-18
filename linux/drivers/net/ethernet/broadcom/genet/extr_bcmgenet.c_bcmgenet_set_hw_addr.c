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
struct bcmgenet_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UMAC_MAC0 ; 
 int /*<<< orphan*/  UMAC_MAC1 ; 
 int /*<<< orphan*/  bcmgenet_umac_writel (struct bcmgenet_priv*,unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcmgenet_set_hw_addr(struct bcmgenet_priv *priv,
				 unsigned char *addr)
{
	bcmgenet_umac_writel(priv, (addr[0] << 24) | (addr[1] << 16) |
			(addr[2] << 8) | addr[3], UMAC_MAC0);
	bcmgenet_umac_writel(priv, (addr[4] << 8) | addr[5], UMAC_MAC1);
}