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
struct sh_eth_private {int speed; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GECMR ; 
 int /*<<< orphan*/  GECMR_10 ; 
 int /*<<< orphan*/  GECMR_100 ; 
 int /*<<< orphan*/  GECMR_1000 ; 
 struct sh_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sh_eth_write (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sh_eth_set_rate_gether(struct net_device *ndev)
{
	struct sh_eth_private *mdp = netdev_priv(ndev);

	switch (mdp->speed) {
	case 10: /* 10BASE */
		sh_eth_write(ndev, GECMR_10, GECMR);
		break;
	case 100:/* 100BASE */
		sh_eth_write(ndev, GECMR_100, GECMR);
		break;
	case 1000: /* 1000BASE */
		sh_eth_write(ndev, GECMR_1000, GECMR);
		break;
	}
}