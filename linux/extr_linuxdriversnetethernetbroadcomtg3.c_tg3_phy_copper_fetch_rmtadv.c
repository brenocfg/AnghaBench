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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  rmt_adv; } ;
struct tg3 {int phy_flags; TYPE_1__ link_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_LPA ; 
 int /*<<< orphan*/  MII_STAT1000 ; 
 int TG3_PHYFLG_10_100_ONLY ; 
 int /*<<< orphan*/  mii_lpa_to_ethtool_lpa_t (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_stat1000_to_ethtool_lpa_t (int /*<<< orphan*/ ) ; 
 scalar_t__ tg3_readphy (struct tg3*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool tg3_phy_copper_fetch_rmtadv(struct tg3 *tp, u32 *rmtadv)
{
	u32 lpeth = 0;

	if (!(tp->phy_flags & TG3_PHYFLG_10_100_ONLY)) {
		u32 val;

		if (tg3_readphy(tp, MII_STAT1000, &val))
			return false;

		lpeth = mii_stat1000_to_ethtool_lpa_t(val);
	}

	if (tg3_readphy(tp, MII_LPA, rmtadv))
		return false;

	lpeth |= mii_lpa_to_ethtool_lpa_t(*rmtadv);
	tp->link_config.rmt_adv = lpeth;

	return true;
}