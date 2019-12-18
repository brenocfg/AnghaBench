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
typedef  int u16 ;
struct bcmgenet_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GENET_IS_V2 (struct bcmgenet_priv*) ; 
 int RBUF_ERR_CNT_V2 ; 
 int RBUF_ERR_CNT_V3PLUS ; 
 int RBUF_OVFL_CNT_V2 ; 
 int RBUF_OVFL_CNT_V3PLUS ; 
#define  UMAC_RBUF_ERR_CNT_V1 129 
#define  UMAC_RBUF_OVFL_CNT_V1 128 
 int /*<<< orphan*/  bcmgenet_rbuf_readl (struct bcmgenet_priv*,int) ; 
 int /*<<< orphan*/  bcmgenet_rbuf_writel (struct bcmgenet_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcmgenet_umac_readl (struct bcmgenet_priv*,int) ; 
 int /*<<< orphan*/  bcmgenet_umac_writel (struct bcmgenet_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 bcmgenet_update_stat_misc(struct bcmgenet_priv *priv, u16 offset)
{
	u16 new_offset;
	u32 val;

	switch (offset) {
	case UMAC_RBUF_OVFL_CNT_V1:
		if (GENET_IS_V2(priv))
			new_offset = RBUF_OVFL_CNT_V2;
		else
			new_offset = RBUF_OVFL_CNT_V3PLUS;

		val = bcmgenet_rbuf_readl(priv,	new_offset);
		/* clear if overflowed */
		if (val == ~0)
			bcmgenet_rbuf_writel(priv, 0, new_offset);
		break;
	case UMAC_RBUF_ERR_CNT_V1:
		if (GENET_IS_V2(priv))
			new_offset = RBUF_ERR_CNT_V2;
		else
			new_offset = RBUF_ERR_CNT_V3PLUS;

		val = bcmgenet_rbuf_readl(priv,	new_offset);
		/* clear if overflowed */
		if (val == ~0)
			bcmgenet_rbuf_writel(priv, 0, new_offset);
		break;
	default:
		val = bcmgenet_umac_readl(priv, offset);
		/* clear if overflowed */
		if (val == ~0)
			bcmgenet_umac_writel(priv, 0, offset);
		break;
	}

	return val;
}