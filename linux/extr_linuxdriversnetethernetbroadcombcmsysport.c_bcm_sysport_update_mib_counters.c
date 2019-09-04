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
struct bcm_sysport_stats {int type; int stat_offset; scalar_t__ stat_sizeof; int /*<<< orphan*/  reg_offset; } ;
struct bcm_sysport_priv {int /*<<< orphan*/  netdev; int /*<<< orphan*/  is_lite; } ;

/* Variables and functions */
 int BCM_SYSPORT_STATS_LEN ; 
#define  BCM_SYSPORT_STAT_MIB_RX 135 
#define  BCM_SYSPORT_STAT_MIB_TX 134 
#define  BCM_SYSPORT_STAT_NETDEV 133 
#define  BCM_SYSPORT_STAT_NETDEV64 132 
#define  BCM_SYSPORT_STAT_RBUF 131 
#define  BCM_SYSPORT_STAT_RUNT 130 
#define  BCM_SYSPORT_STAT_RXCHK 129 
#define  BCM_SYSPORT_STAT_SOFT 128 
 int /*<<< orphan*/  UMAC_MIB_START ; 
 scalar_t__ UMAC_MIB_STAT_OFFSET ; 
 struct bcm_sysport_stats* bcm_sysport_gstrings_stats ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  netif_dbg (struct bcm_sysport_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rbuf_readl (struct bcm_sysport_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rbuf_writel (struct bcm_sysport_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxchk_readl (struct bcm_sysport_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxchk_writel (struct bcm_sysport_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umac_readl (struct bcm_sysport_priv*,scalar_t__) ; 

__attribute__((used)) static void bcm_sysport_update_mib_counters(struct bcm_sysport_priv *priv)
{
	int i, j = 0;

	for (i = 0; i < BCM_SYSPORT_STATS_LEN; i++) {
		const struct bcm_sysport_stats *s;
		u8 offset = 0;
		u32 val = 0;
		char *p;

		s = &bcm_sysport_gstrings_stats[i];
		switch (s->type) {
		case BCM_SYSPORT_STAT_NETDEV:
		case BCM_SYSPORT_STAT_NETDEV64:
		case BCM_SYSPORT_STAT_SOFT:
			continue;
		case BCM_SYSPORT_STAT_MIB_RX:
		case BCM_SYSPORT_STAT_MIB_TX:
		case BCM_SYSPORT_STAT_RUNT:
			if (priv->is_lite)
				continue;

			if (s->type != BCM_SYSPORT_STAT_MIB_RX)
				offset = UMAC_MIB_STAT_OFFSET;
			val = umac_readl(priv, UMAC_MIB_START + j + offset);
			break;
		case BCM_SYSPORT_STAT_RXCHK:
			val = rxchk_readl(priv, s->reg_offset);
			if (val == ~0)
				rxchk_writel(priv, 0, s->reg_offset);
			break;
		case BCM_SYSPORT_STAT_RBUF:
			val = rbuf_readl(priv, s->reg_offset);
			if (val == ~0)
				rbuf_writel(priv, 0, s->reg_offset);
			break;
		}

		j += s->stat_sizeof;
		p = (char *)priv + s->stat_offset;
		*(u32 *)p = val;
	}

	netif_dbg(priv, hw, priv->netdev, "updated MIB counters\n");
}