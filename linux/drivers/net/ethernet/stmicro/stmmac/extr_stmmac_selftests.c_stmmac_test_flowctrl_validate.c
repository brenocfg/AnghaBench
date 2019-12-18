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
struct stmmac_test_priv {int ok; int /*<<< orphan*/  comp; } ;
struct sk_buff {int dummy; } ;
struct packet_type {struct stmmac_test_priv* af_packet_priv; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct ethhdr {scalar_t__ h_proto; int /*<<< orphan*/  h_source; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_PAUSE ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ skb_mac_header (struct sk_buff*) ; 

__attribute__((used)) static int stmmac_test_flowctrl_validate(struct sk_buff *skb,
					 struct net_device *ndev,
					 struct packet_type *pt,
					 struct net_device *orig_ndev)
{
	struct stmmac_test_priv *tpriv = pt->af_packet_priv;
	struct ethhdr *ehdr;

	ehdr = (struct ethhdr *)skb_mac_header(skb);
	if (!ether_addr_equal(ehdr->h_source, orig_ndev->dev_addr))
		goto out;
	if (ehdr->h_proto != htons(ETH_P_PAUSE))
		goto out;

	tpriv->ok = true;
	complete(&tpriv->comp);
out:
	kfree_skb(skb);
	return 0;
}