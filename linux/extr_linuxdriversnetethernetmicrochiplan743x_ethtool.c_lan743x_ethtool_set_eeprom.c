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
typedef  scalar_t__ u8 ;
struct net_device {int dummy; } ;
struct lan743x_adapter {int dummy; } ;
struct ethtool_eeprom {scalar_t__ magic; int /*<<< orphan*/  len; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ LAN743X_EEPROM_MAGIC ; 
 scalar_t__ LAN743X_OTP_MAGIC ; 
 int /*<<< orphan*/  MAX_EEPROM_SIZE ; 
 scalar_t__ OTP_INDICATOR_1 ; 
 int lan743x_eeprom_write (struct lan743x_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int lan743x_otp_write (struct lan743x_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 struct lan743x_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int lan743x_ethtool_set_eeprom(struct net_device *netdev,
				      struct ethtool_eeprom *ee, u8 *data)
{
	struct lan743x_adapter *adapter = netdev_priv(netdev);
	int ret = -EINVAL;

	if (ee->magic == LAN743X_EEPROM_MAGIC)
		ret = lan743x_eeprom_write(adapter, ee->offset, ee->len,
					   data);
	/* Beware!  OTP is One Time Programming ONLY!
	 * So do some strict condition check before messing up
	 */
	else if ((ee->magic == LAN743X_OTP_MAGIC) &&
		 (ee->offset == 0) &&
		 (ee->len == MAX_EEPROM_SIZE) &&
		 (data[0] == OTP_INDICATOR_1))
		ret = lan743x_otp_write(adapter, ee->offset, ee->len, data);

	return ret;
}