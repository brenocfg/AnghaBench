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
typedef  int /*<<< orphan*/  u8 ;
struct smc911x_local {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMC_SET_E2P_DATA (struct smc911x_local*,int /*<<< orphan*/ ) ; 
 struct smc911x_local* netdev_priv (struct net_device*) ; 
 int smc911x_ethtool_wait_eeprom_ready (struct net_device*) ; 

__attribute__((used)) static inline int smc911x_ethtool_write_eeprom_byte(struct net_device *dev,
													 u8 data)
{
	struct smc911x_local *lp = netdev_priv(dev);
	int ret;

	if ((ret = smc911x_ethtool_wait_eeprom_ready(dev))!=0)
		return ret;
	SMC_SET_E2P_DATA(lp, data);
	return 0;
}