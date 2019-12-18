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
struct spider_net_card {int dummy; } ;
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int* dev_addr; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  SPIDER_NET_GMACOPEMD ; 
 int /*<<< orphan*/  SPIDER_NET_GMACUNIMACL ; 
 int /*<<< orphan*/  SPIDER_NET_GMACUNIMACU ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct spider_net_card* netdev_priv (struct net_device*) ; 
 int spider_net_read_reg (struct spider_net_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spider_net_set_promisc (struct spider_net_card*) ; 
 int /*<<< orphan*/  spider_net_write_reg (struct spider_net_card*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
spider_net_set_mac(struct net_device *netdev, void *p)
{
	struct spider_net_card *card = netdev_priv(netdev);
	u32 macl, macu, regvalue;
	struct sockaddr *addr = p;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	memcpy(netdev->dev_addr, addr->sa_data, ETH_ALEN);

	/* switch off GMACTPE and GMACRPE */
	regvalue = spider_net_read_reg(card, SPIDER_NET_GMACOPEMD);
	regvalue &= ~((1 << 5) | (1 << 6));
	spider_net_write_reg(card, SPIDER_NET_GMACOPEMD, regvalue);

	/* write mac */
	macu = (netdev->dev_addr[0]<<24) + (netdev->dev_addr[1]<<16) +
		(netdev->dev_addr[2]<<8) + (netdev->dev_addr[3]);
	macl = (netdev->dev_addr[4]<<8) + (netdev->dev_addr[5]);
	spider_net_write_reg(card, SPIDER_NET_GMACUNIMACU, macu);
	spider_net_write_reg(card, SPIDER_NET_GMACUNIMACL, macl);

	/* switch GMACTPE and GMACRPE back on */
	regvalue = spider_net_read_reg(card, SPIDER_NET_GMACOPEMD);
	regvalue |= ((1 << 5) | (1 << 6));
	spider_net_write_reg(card, SPIDER_NET_GMACOPEMD, regvalue);

	spider_net_set_promisc(card);

	return 0;
}