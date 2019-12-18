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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct net_device {int dummy; } ;
struct cpsw_common {int /*<<< orphan*/  tx_ch_num; int /*<<< orphan*/  rx_ch_num; } ;
struct TYPE_2__ {int /*<<< orphan*/  stat_string; } ;

/* Variables and functions */
 int CPSW_STATS_COMMON_LEN ; 
 int /*<<< orphan*/  ETH_GSTRING_LEN ; 
#define  ETH_SS_STATS 128 
 int /*<<< orphan*/  cpsw_add_ch_strings (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* cpsw_gstrings_stats ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cpsw_common* ndev_to_cpsw (struct net_device*) ; 

void cpsw_get_strings(struct net_device *ndev, u32 stringset, u8 *data)
{
	struct cpsw_common *cpsw = ndev_to_cpsw(ndev);
	u8 *p = data;
	int i;

	switch (stringset) {
	case ETH_SS_STATS:
		for (i = 0; i < CPSW_STATS_COMMON_LEN; i++) {
			memcpy(p, cpsw_gstrings_stats[i].stat_string,
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		}

		cpsw_add_ch_strings(&p, cpsw->rx_ch_num, 1);
		cpsw_add_ch_strings(&p, cpsw->tx_ch_num, 0);
		break;
	}
}