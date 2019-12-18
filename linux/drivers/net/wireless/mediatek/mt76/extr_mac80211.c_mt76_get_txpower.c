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
struct mt76_dev {int /*<<< orphan*/  txpower_cur; int /*<<< orphan*/  antenna_mask; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct mt76_dev* priv; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int hweight8 (int /*<<< orphan*/ ) ; 

int mt76_get_txpower(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
		     int *dbm)
{
	struct mt76_dev *dev = hw->priv;
	int n_chains = hweight8(dev->antenna_mask);

	*dbm = DIV_ROUND_UP(dev->txpower_cur, 2);

	/* convert from per-chain power to combined
	 * output power
	 */
	switch (n_chains) {
	case 4:
		*dbm += 6;
		break;
	case 3:
		*dbm += 4;
		break;
	case 2:
		*dbm += 3;
		break;
	default:
		break;
	}

	return 0;
}