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
struct antenna_setup {int /*<<< orphan*/  rx; int /*<<< orphan*/  tx; } ;
struct link_ant {int flags; struct antenna_setup active; } ;
struct TYPE_2__ {struct link_ant ant; } ;
struct rt2x00_dev {TYPE_1__ link; } ;
struct ieee80211_hw {struct rt2x00_dev* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANTENNA_HW_DIVERSITY ; 
 int ANTENNA_RX_DIVERSITY ; 
 int ANTENNA_TX_DIVERSITY ; 

int rt2x00mac_get_antenna(struct ieee80211_hw *hw, u32 *tx_ant, u32 *rx_ant)
{
	struct rt2x00_dev *rt2x00dev = hw->priv;
	struct link_ant *ant = &rt2x00dev->link.ant;
	struct antenna_setup *active = &rt2x00dev->link.ant.active;

	// When software diversity is active, we must report this to the
	// client and not the current active antenna state.
	if (ant->flags & ANTENNA_TX_DIVERSITY)
		*tx_ant = ANTENNA_HW_DIVERSITY;
	else
		*tx_ant = active->tx;

	if (ant->flags & ANTENNA_RX_DIVERSITY)
		*rx_ant = ANTENNA_HW_DIVERSITY;
	else
		*rx_ant = active->rx;

	return 0;
}