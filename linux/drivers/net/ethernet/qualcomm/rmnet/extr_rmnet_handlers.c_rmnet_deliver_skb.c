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
struct sk_buff {int /*<<< orphan*/  pkt_type; int /*<<< orphan*/  dev; } ;
struct rmnet_priv {int /*<<< orphan*/  gro_cells; } ;

/* Variables and functions */
 int /*<<< orphan*/  PACKET_HOST ; 
 int /*<<< orphan*/  gro_cells_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct rmnet_priv* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmnet_vnd_rx_fixup (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_mac_header (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rmnet_deliver_skb(struct sk_buff *skb)
{
	struct rmnet_priv *priv = netdev_priv(skb->dev);

	skb_reset_transport_header(skb);
	skb_reset_network_header(skb);
	rmnet_vnd_rx_fixup(skb, skb->dev);

	skb->pkt_type = PACKET_HOST;
	skb_set_mac_header(skb, 0);
	gro_cells_receive(&priv->gro_cells, skb);
}