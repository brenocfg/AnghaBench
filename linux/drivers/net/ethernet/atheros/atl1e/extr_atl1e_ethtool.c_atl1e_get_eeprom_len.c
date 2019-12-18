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
struct atl1e_adapter {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int AT_EEPROM_LEN ; 
 int /*<<< orphan*/  atl1e_check_eeprom_exist (int /*<<< orphan*/ *) ; 
 struct atl1e_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int atl1e_get_eeprom_len(struct net_device *netdev)
{
	struct atl1e_adapter *adapter = netdev_priv(netdev);

	if (!atl1e_check_eeprom_exist(&adapter->hw))
		return AT_EEPROM_LEN;
	else
		return 0;
}