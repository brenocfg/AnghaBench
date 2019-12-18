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
typedef  scalar_t__ u32 ;
struct tg3 {int /*<<< orphan*/  lock; } ;
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  ENABLE_ASF ; 
 int /*<<< orphan*/  MAC_ADDR_0_HIGH ; 
 int /*<<< orphan*/  MAC_ADDR_0_LOW ; 
 int /*<<< orphan*/  MAC_ADDR_1_HIGH ; 
 int /*<<< orphan*/  MAC_ADDR_1_LOW ; 
 int /*<<< orphan*/  __tg3_set_mac_addr (struct tg3*,int) ; 
 int /*<<< orphan*/  __tg3_set_rx_mode (struct net_device*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tg3* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 
 scalar_t__ tr32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tg3_set_mac_addr(struct net_device *dev, void *p)
{
	struct tg3 *tp = netdev_priv(dev);
	struct sockaddr *addr = p;
	int err = 0;
	bool skip_mac_1 = false;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	memcpy(dev->dev_addr, addr->sa_data, dev->addr_len);

	if (!netif_running(dev))
		return 0;

	if (tg3_flag(tp, ENABLE_ASF)) {
		u32 addr0_high, addr0_low, addr1_high, addr1_low;

		addr0_high = tr32(MAC_ADDR_0_HIGH);
		addr0_low = tr32(MAC_ADDR_0_LOW);
		addr1_high = tr32(MAC_ADDR_1_HIGH);
		addr1_low = tr32(MAC_ADDR_1_LOW);

		/* Skip MAC addr 1 if ASF is using it. */
		if ((addr0_high != addr1_high || addr0_low != addr1_low) &&
		    !(addr1_high == 0 && addr1_low == 0))
			skip_mac_1 = true;
	}
	spin_lock_bh(&tp->lock);
	__tg3_set_mac_addr(tp, skip_mac_1);
	__tg3_set_rx_mode(dev);
	spin_unlock_bh(&tp->lock);

	return err;
}