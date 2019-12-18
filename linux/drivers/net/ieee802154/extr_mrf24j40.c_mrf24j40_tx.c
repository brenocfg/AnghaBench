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
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct mrf24j40 {struct sk_buff* tx_skb; } ;
struct ieee802154_hw {struct mrf24j40* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printdev (struct mrf24j40*) ; 
 int write_tx_buf (struct mrf24j40*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mrf24j40_tx(struct ieee802154_hw *hw, struct sk_buff *skb)
{
	struct mrf24j40 *devrec = hw->priv;

	dev_dbg(printdev(devrec), "tx packet of %d bytes\n", skb->len);
	devrec->tx_skb = skb;

	return write_tx_buf(devrec, 0x000, skb->data, skb->len);
}