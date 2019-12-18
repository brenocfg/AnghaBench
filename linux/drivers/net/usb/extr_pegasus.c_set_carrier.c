#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  phy; } ;
typedef  TYPE_1__ pegasus_t ;

/* Variables and functions */
 int BMSR_LSTATUS ; 
 int /*<<< orphan*/  MII_BMSR ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 scalar_t__ read_mii_word (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void set_carrier(struct net_device *net)
{
	pegasus_t *pegasus = netdev_priv(net);
	u16 tmp;

	if (read_mii_word(pegasus, pegasus->phy, MII_BMSR, &tmp))
		return;

	if (tmp & BMSR_LSTATUS)
		netif_carrier_on(net);
	else
		netif_carrier_off(net);
}