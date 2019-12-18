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
struct net_device {int dummy; } ;
struct at91_priv {scalar_t__ rx_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_SR ; 
 int /*<<< orphan*/  at91_activate_rx_low (struct at91_priv*) ; 
 int /*<<< orphan*/  at91_activate_rx_mb (struct at91_priv*,unsigned int) ; 
 int at91_read (struct at91_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_read_msg (struct net_device*,unsigned int) ; 
 unsigned int find_next_bit (unsigned long const*,unsigned int,scalar_t__) ; 
 scalar_t__ get_mb_rx_first (struct at91_priv*) ; 
 unsigned int get_mb_rx_last (struct at91_priv*) ; 
 scalar_t__ get_mb_rx_low_last (struct at91_priv*) ; 
 int get_mb_rx_low_mask (struct at91_priv*) ; 
 unsigned int get_mb_tx_first (struct at91_priv*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct at91_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int at91_poll_rx(struct net_device *dev, int quota)
{
	struct at91_priv *priv = netdev_priv(dev);
	u32 reg_sr = at91_read(priv, AT91_SR);
	const unsigned long *addr = (unsigned long *)&reg_sr;
	unsigned int mb;
	int received = 0;

	if (priv->rx_next > get_mb_rx_low_last(priv) &&
	    reg_sr & get_mb_rx_low_mask(priv))
		netdev_info(dev,
			"order of incoming frames cannot be guaranteed\n");

 again:
	for (mb = find_next_bit(addr, get_mb_tx_first(priv), priv->rx_next);
	     mb < get_mb_tx_first(priv) && quota > 0;
	     reg_sr = at91_read(priv, AT91_SR),
	     mb = find_next_bit(addr, get_mb_tx_first(priv), ++priv->rx_next)) {
		at91_read_msg(dev, mb);

		/* reactivate mailboxes */
		if (mb == get_mb_rx_low_last(priv))
			/* all lower mailboxed, if just finished it */
			at91_activate_rx_low(priv);
		else if (mb > get_mb_rx_low_last(priv))
			/* only the mailbox we read */
			at91_activate_rx_mb(priv, mb);

		received++;
		quota--;
	}

	/* upper group completed, look again in lower */
	if (priv->rx_next > get_mb_rx_low_last(priv) &&
	    mb > get_mb_rx_last(priv)) {
		priv->rx_next = get_mb_rx_first(priv);
		if (quota > 0)
			goto again;
	}

	return received;
}