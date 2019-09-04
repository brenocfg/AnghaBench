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
struct bcmgenet_priv {int dummy; } ;

/* Variables and functions */
 int MAX_MC_COUNT ; 
 scalar_t__ UMAC_MDF_ADDR ; 
 scalar_t__ UMAC_MDF_CTRL ; 
 int bcmgenet_umac_readl (struct bcmgenet_priv*,scalar_t__) ; 
 int /*<<< orphan*/  bcmgenet_umac_writel (struct bcmgenet_priv*,int,scalar_t__) ; 

__attribute__((used)) static inline void bcmgenet_set_mdf_addr(struct bcmgenet_priv *priv,
					 unsigned char *addr,
					 int *i,
					 int *mc)
{
	u32 reg;

	bcmgenet_umac_writel(priv, addr[0] << 8 | addr[1],
			     UMAC_MDF_ADDR + (*i * 4));
	bcmgenet_umac_writel(priv, addr[2] << 24 | addr[3] << 16 |
			     addr[4] << 8 | addr[5],
			     UMAC_MDF_ADDR + ((*i + 1) * 4));
	reg = bcmgenet_umac_readl(priv, UMAC_MDF_CTRL);
	reg |= (1 << (MAX_MC_COUNT - *mc));
	bcmgenet_umac_writel(priv, reg, UMAC_MDF_CTRL);
	*i += 2;
	(*mc)++;
}