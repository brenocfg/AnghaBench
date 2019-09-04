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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct bcmgenet_stats {int type; int stat_offset; scalar_t__ stat_sizeof; scalar_t__ reg_offset; } ;
struct bcmgenet_priv {int dummy; } ;

/* Variables and functions */
 int BCMGENET_STATS_LEN ; 
#define  BCMGENET_STAT_MIB_RX 133 
#define  BCMGENET_STAT_MIB_TX 132 
#define  BCMGENET_STAT_MISC 131 
#define  BCMGENET_STAT_NETDEV 130 
 scalar_t__ BCMGENET_STAT_OFFSET ; 
#define  BCMGENET_STAT_RUNT 129 
#define  BCMGENET_STAT_SOFT 128 
 int /*<<< orphan*/  GENET_IS_V1 (struct bcmgenet_priv*) ; 
 int /*<<< orphan*/  UMAC_MIB_START ; 
 struct bcmgenet_stats* bcmgenet_gstrings_stats ; 
 int /*<<< orphan*/  bcmgenet_umac_readl (struct bcmgenet_priv*,scalar_t__) ; 
 int /*<<< orphan*/  bcmgenet_umac_writel (struct bcmgenet_priv*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bcmgenet_update_stat_misc (struct bcmgenet_priv*,scalar_t__) ; 

__attribute__((used)) static void bcmgenet_update_mib_counters(struct bcmgenet_priv *priv)
{
	int i, j = 0;

	for (i = 0; i < BCMGENET_STATS_LEN; i++) {
		const struct bcmgenet_stats *s;
		u8 offset = 0;
		u32 val = 0;
		char *p;

		s = &bcmgenet_gstrings_stats[i];
		switch (s->type) {
		case BCMGENET_STAT_NETDEV:
		case BCMGENET_STAT_SOFT:
			continue;
		case BCMGENET_STAT_RUNT:
			offset += BCMGENET_STAT_OFFSET;
			/* fall through */
		case BCMGENET_STAT_MIB_TX:
			offset += BCMGENET_STAT_OFFSET;
			/* fall through */
		case BCMGENET_STAT_MIB_RX:
			val = bcmgenet_umac_readl(priv,
						  UMAC_MIB_START + j + offset);
			offset = 0;	/* Reset Offset */
			break;
		case BCMGENET_STAT_MISC:
			if (GENET_IS_V1(priv)) {
				val = bcmgenet_umac_readl(priv, s->reg_offset);
				/* clear if overflowed */
				if (val == ~0)
					bcmgenet_umac_writel(priv, 0,
							     s->reg_offset);
			} else {
				val = bcmgenet_update_stat_misc(priv,
								s->reg_offset);
			}
			break;
		}

		j += s->stat_sizeof;
		p = (char *)priv + s->stat_offset;
		*(u32 *)p = val;
	}
}