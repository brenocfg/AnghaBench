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
struct net_device {int dummy; } ;
struct ks8851_net {int rc_ccr; } ;

/* Variables and functions */
 int CCR_EEPROM ; 
 struct ks8851_net* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ks8851_get_eeprom_len(struct net_device *dev)
{
	struct ks8851_net *ks = netdev_priv(dev);

	/* currently, we assume it is an 93C46 attached, so return 128 */
	return ks->rc_ccr & CCR_EEPROM ? 128 : 0;
}