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
struct atl2_adapter {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  atl2_check_eeprom_exist (int /*<<< orphan*/ *) ; 
 struct atl2_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int atl2_get_eeprom_len(struct net_device *netdev)
{
	struct atl2_adapter *adapter = netdev_priv(netdev);

	if (!atl2_check_eeprom_exist(&adapter->hw))
		return 512;
	else
		return 0;
}