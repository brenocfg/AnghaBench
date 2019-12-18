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
typedef  int u16 ;
struct sk_buff {scalar_t__ data; } ;
struct p54_trap {int /*<<< orphan*/  frequency; int /*<<< orphan*/  event; } ;
struct p54_hdr {scalar_t__ data; } ;
struct p54_common {TYPE_1__* hw; int /*<<< orphan*/  vif; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
#define  P54_TRAP_BEACON_TX 135 
#define  P54_TRAP_FAA_RADIO_OFF 134 
#define  P54_TRAP_FAA_RADIO_ON 133 
#define  P54_TRAP_NO_BEACON 132 
#define  P54_TRAP_RADAR 131 
#define  P54_TRAP_SCAN 130 
#define  P54_TRAP_TBTT 129 
#define  P54_TRAP_TIMER 128 
 int /*<<< orphan*/  ieee80211_beacon_loss (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_info (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  wiphy_rfkill_set_hw_state (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void p54_rx_trap(struct p54_common *priv, struct sk_buff *skb)
{
	struct p54_hdr *hdr = (struct p54_hdr *) skb->data;
	struct p54_trap *trap = (struct p54_trap *) hdr->data;
	u16 event = le16_to_cpu(trap->event);
	u16 freq = le16_to_cpu(trap->frequency);

	switch (event) {
	case P54_TRAP_BEACON_TX:
		break;
	case P54_TRAP_RADAR:
		wiphy_info(priv->hw->wiphy, "radar (freq:%d MHz)\n", freq);
		break;
	case P54_TRAP_NO_BEACON:
		if (priv->vif)
			ieee80211_beacon_loss(priv->vif);
		break;
	case P54_TRAP_SCAN:
		break;
	case P54_TRAP_TBTT:
		break;
	case P54_TRAP_TIMER:
		break;
	case P54_TRAP_FAA_RADIO_OFF:
		wiphy_rfkill_set_hw_state(priv->hw->wiphy, true);
		break;
	case P54_TRAP_FAA_RADIO_ON:
		wiphy_rfkill_set_hw_state(priv->hw->wiphy, false);
		break;
	default:
		wiphy_info(priv->hw->wiphy, "received event:%x freq:%d\n",
			   event, freq);
		break;
	}
}