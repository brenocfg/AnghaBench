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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int* dev_addr; int /*<<< orphan*/  addr_len; } ;
struct fec_enet_private {scalar_t__ hwp; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 scalar_t__ FEC_ADDR_HIGH ; 
 scalar_t__ FEC_ADDR_LOW ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int
fec_set_mac_address(struct net_device *ndev, void *p)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	struct sockaddr *addr = p;

	if (addr) {
		if (!is_valid_ether_addr(addr->sa_data))
			return -EADDRNOTAVAIL;
		memcpy(ndev->dev_addr, addr->sa_data, ndev->addr_len);
	}

	/* Add netif status check here to avoid system hang in below case:
	 * ifconfig ethx down; ifconfig ethx hw ether xx:xx:xx:xx:xx:xx;
	 * After ethx down, fec all clocks are gated off and then register
	 * access causes system hang.
	 */
	if (!netif_running(ndev))
		return 0;

	writel(ndev->dev_addr[3] | (ndev->dev_addr[2] << 8) |
		(ndev->dev_addr[1] << 16) | (ndev->dev_addr[0] << 24),
		fep->hwp + FEC_ADDR_LOW);
	writel((ndev->dev_addr[5] << 16) | (ndev->dev_addr[4] << 24),
		fep->hwp + FEC_ADDR_HIGH);
	return 0;
}