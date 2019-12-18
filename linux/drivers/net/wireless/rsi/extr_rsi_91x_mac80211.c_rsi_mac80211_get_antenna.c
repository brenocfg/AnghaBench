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
struct rsi_hw {struct rsi_common* priv; } ;
struct rsi_common {scalar_t__ ant_in_use; int /*<<< orphan*/  mutex; } ;
struct ieee80211_hw {struct rsi_hw* priv; } ;

/* Variables and functions */
 scalar_t__ ANTENNA_SEL_UFL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rsi_mac80211_get_antenna(struct ieee80211_hw *hw,
				    u32 *tx_ant, u32 *rx_ant)
{
	struct rsi_hw *adapter = hw->priv;
	struct rsi_common *common = adapter->priv;

	mutex_lock(&common->mutex);

	*tx_ant = (common->ant_in_use == ANTENNA_SEL_UFL) ? 1 : 0;
	*rx_ant = 0;

	mutex_unlock(&common->mutex);
	
	return 0;	
}