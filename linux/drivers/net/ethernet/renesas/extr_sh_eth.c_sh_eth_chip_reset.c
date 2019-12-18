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
struct sh_eth_private {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARSTR ; 
 int /*<<< orphan*/  ARSTR_ARST ; 
 int /*<<< orphan*/  mdelay (int) ; 
 struct sh_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sh_eth_tsu_write (struct sh_eth_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sh_eth_chip_reset(struct net_device *ndev)
{
	struct sh_eth_private *mdp = netdev_priv(ndev);

	/* reset device */
	sh_eth_tsu_write(mdp, ARSTR_ARST, ARSTR);
	mdelay(1);
}