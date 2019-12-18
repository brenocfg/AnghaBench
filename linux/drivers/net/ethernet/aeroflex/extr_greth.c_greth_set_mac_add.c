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
struct greth_regs {int /*<<< orphan*/  esa_lsb; int /*<<< orphan*/  esa_msb; } ;
struct greth_private {struct greth_regs* regs; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  GRETH_REGSAVE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct greth_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int greth_set_mac_add(struct net_device *dev, void *p)
{
	struct sockaddr *addr = p;
	struct greth_private *greth;
	struct greth_regs *regs;

	greth = netdev_priv(dev);
	regs = greth->regs;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	memcpy(dev->dev_addr, addr->sa_data, dev->addr_len);
	GRETH_REGSAVE(regs->esa_msb, dev->dev_addr[0] << 8 | dev->dev_addr[1]);
	GRETH_REGSAVE(regs->esa_lsb, dev->dev_addr[2] << 24 | dev->dev_addr[3] << 16 |
		      dev->dev_addr[4] << 8 | dev->dev_addr[5]);

	return 0;
}