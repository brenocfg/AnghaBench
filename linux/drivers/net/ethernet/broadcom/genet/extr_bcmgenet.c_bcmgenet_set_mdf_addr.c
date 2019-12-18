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
 scalar_t__ UMAC_MDF_ADDR ; 
 int /*<<< orphan*/  bcmgenet_umac_writel (struct bcmgenet_priv*,unsigned char,scalar_t__) ; 

__attribute__((used)) static inline void bcmgenet_set_mdf_addr(struct bcmgenet_priv *priv,
					 unsigned char *addr,
					 int *i)
{
	bcmgenet_umac_writel(priv, addr[0] << 8 | addr[1],
			     UMAC_MDF_ADDR + (*i * 4));
	bcmgenet_umac_writel(priv, addr[2] << 24 | addr[3] << 16 |
			     addr[4] << 8 | addr[5],
			     UMAC_MDF_ADDR + ((*i + 1) * 4));
	*i += 2;
}