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
struct sk_buff {scalar_t__ data; } ;
struct p54_hdr {int /*<<< orphan*/  type; } ;
struct p54_common {TYPE_1__* hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
#define  P54_CONTROL_TYPE_BBP 132 
#define  P54_CONTROL_TYPE_EEPROM_READBACK 131 
#define  P54_CONTROL_TYPE_STAT_READBACK 130 
#define  P54_CONTROL_TYPE_TRAP 129 
#define  P54_CONTROL_TYPE_TXDONE 128 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p54_rx_eeprom_readback (struct p54_common*,struct sk_buff*) ; 
 int /*<<< orphan*/  p54_rx_frame_sent (struct p54_common*,struct sk_buff*) ; 
 int /*<<< orphan*/  p54_rx_stats (struct p54_common*,struct sk_buff*) ; 
 int /*<<< orphan*/  p54_rx_trap (struct p54_common*,struct sk_buff*) ; 
 int /*<<< orphan*/  wiphy_debug (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int p54_rx_control(struct p54_common *priv, struct sk_buff *skb)
{
	struct p54_hdr *hdr = (struct p54_hdr *) skb->data;

	switch (le16_to_cpu(hdr->type)) {
	case P54_CONTROL_TYPE_TXDONE:
		p54_rx_frame_sent(priv, skb);
		break;
	case P54_CONTROL_TYPE_TRAP:
		p54_rx_trap(priv, skb);
		break;
	case P54_CONTROL_TYPE_BBP:
		break;
	case P54_CONTROL_TYPE_STAT_READBACK:
		p54_rx_stats(priv, skb);
		break;
	case P54_CONTROL_TYPE_EEPROM_READBACK:
		p54_rx_eeprom_readback(priv, skb);
		break;
	default:
		wiphy_debug(priv->hw->wiphy,
			    "not handling 0x%02x type control frame\n",
			    le16_to_cpu(hdr->type));
		break;
	}
	return 0;
}