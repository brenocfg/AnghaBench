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
struct qlcnic_adapter {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ qlcnic_82xx_check (struct qlcnic_adapter*) ; 
 int qlcnic_83xx_flash_test (struct qlcnic_adapter*) ; 

__attribute__((used)) static int qlcnic_eeprom_test(struct net_device *dev)
{
	struct qlcnic_adapter *adapter = netdev_priv(dev);

	if (qlcnic_82xx_check(adapter))
		return 0;

	return qlcnic_83xx_flash_test(adapter);
}