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
struct lan78xx_net {int /*<<< orphan*/  intf; } ;
struct ethtool_eeprom {scalar_t__ magic; int len; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 scalar_t__ LAN78XX_EEPROM_MAGIC ; 
 scalar_t__ LAN78XX_OTP_MAGIC ; 
 scalar_t__ OTP_INDICATOR_1 ; 
 int lan78xx_write_raw_eeprom (struct lan78xx_net*,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int lan78xx_write_raw_otp (struct lan78xx_net*,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 struct lan78xx_net* netdev_priv (struct net_device*) ; 
 int usb_autopm_get_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lan78xx_ethtool_set_eeprom(struct net_device *netdev,
				      struct ethtool_eeprom *ee, u8 *data)
{
	struct lan78xx_net *dev = netdev_priv(netdev);
	int ret;

	ret = usb_autopm_get_interface(dev->intf);
	if (ret)
		return ret;

	/* Invalid EEPROM_INDICATOR at offset zero will result in a failure
	 * to load data from EEPROM
	 */
	if (ee->magic == LAN78XX_EEPROM_MAGIC)
		ret = lan78xx_write_raw_eeprom(dev, ee->offset, ee->len, data);
	else if ((ee->magic == LAN78XX_OTP_MAGIC) &&
		 (ee->offset == 0) &&
		 (ee->len == 512) &&
		 (data[0] == OTP_INDICATOR_1))
		ret = lan78xx_write_raw_otp(dev, ee->offset, ee->len, data);

	usb_autopm_put_interface(dev->intf);

	return ret;
}