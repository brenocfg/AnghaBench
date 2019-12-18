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
struct net_device {int dummy; } ;
struct lan743x_adapter {int flags; } ;
struct ethtool_eeprom {int /*<<< orphan*/  len; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int LAN743X_ADAPTER_FLAG_OTP ; 
 int lan743x_eeprom_read (struct lan743x_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int lan743x_otp_read (struct lan743x_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct lan743x_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int lan743x_ethtool_get_eeprom(struct net_device *netdev,
				      struct ethtool_eeprom *ee, u8 *data)
{
	struct lan743x_adapter *adapter = netdev_priv(netdev);
	int ret = 0;

	if (adapter->flags & LAN743X_ADAPTER_FLAG_OTP)
		ret = lan743x_otp_read(adapter, ee->offset, ee->len, data);
	else
		ret = lan743x_eeprom_read(adapter, ee->offset, ee->len, data);

	return ret;
}