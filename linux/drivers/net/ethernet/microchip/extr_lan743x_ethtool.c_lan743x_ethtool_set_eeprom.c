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
struct ethtool_eeprom {scalar_t__ magic; int /*<<< orphan*/  len; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int EINVAL ; 
 int LAN743X_ADAPTER_FLAG_OTP ; 
 scalar_t__ LAN743X_EEPROM_MAGIC ; 
 scalar_t__ LAN743X_OTP_MAGIC ; 
 int lan743x_eeprom_write (struct lan743x_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int lan743x_otp_write (struct lan743x_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct lan743x_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int lan743x_ethtool_set_eeprom(struct net_device *netdev,
				      struct ethtool_eeprom *ee, u8 *data)
{
	struct lan743x_adapter *adapter = netdev_priv(netdev);
	int ret = -EINVAL;

	if (adapter->flags & LAN743X_ADAPTER_FLAG_OTP) {
		/* Beware!  OTP is One Time Programming ONLY! */
		if (ee->magic == LAN743X_OTP_MAGIC) {
			ret = lan743x_otp_write(adapter, ee->offset,
						ee->len, data);
		}
	} else {
		if (ee->magic == LAN743X_EEPROM_MAGIC) {
			ret = lan743x_eeprom_write(adapter, ee->offset,
						   ee->len, data);
		}
	}

	return ret;
}