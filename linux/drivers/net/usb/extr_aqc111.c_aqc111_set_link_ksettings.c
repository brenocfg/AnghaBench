#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct usbnet {TYPE_1__* udev; struct aqc111_data* driver_priv; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ autoneg; scalar_t__ speed; scalar_t__ duplex; } ;
struct ethtool_link_ksettings {TYPE_2__ base; } ;
struct aqc111_data {scalar_t__ autoneg; scalar_t__ advertised_speed; } ;
typedef  enum usb_device_speed { ____Placeholder_usb_device_speed } usb_device_speed ;
struct TYPE_3__ {int speed; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_DISABLE ; 
 scalar_t__ AUTONEG_ENABLE ; 
 scalar_t__ DUPLEX_FULL ; 
 int EINVAL ; 
 scalar_t__ SPEED_100 ; 
 scalar_t__ SPEED_1000 ; 
 scalar_t__ SPEED_2500 ; 
 scalar_t__ SPEED_5000 ; 
 scalar_t__ SPEED_UNKNOWN ; 
 int USB_SPEED_SUPER ; 
 int /*<<< orphan*/  aqc111_set_phy_speed (struct usbnet*,scalar_t__,scalar_t__) ; 
 struct usbnet* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int aqc111_set_link_ksettings(struct net_device *net,
				     const struct ethtool_link_ksettings *elk)
{
	struct usbnet *dev = netdev_priv(net);
	struct aqc111_data *aqc111_data = dev->driver_priv;
	enum usb_device_speed usb_speed = dev->udev->speed;
	u8 autoneg = elk->base.autoneg;
	u32 speed = elk->base.speed;

	if (autoneg == AUTONEG_ENABLE) {
		if (aqc111_data->autoneg != AUTONEG_ENABLE) {
			aqc111_data->autoneg = AUTONEG_ENABLE;
			aqc111_data->advertised_speed =
					(usb_speed == USB_SPEED_SUPER) ?
					 SPEED_5000 : SPEED_1000;
			aqc111_set_phy_speed(dev, aqc111_data->autoneg,
					     aqc111_data->advertised_speed);
		}
	} else {
		if (speed != SPEED_100 &&
		    speed != SPEED_1000 &&
		    speed != SPEED_2500 &&
		    speed != SPEED_5000 &&
		    speed != SPEED_UNKNOWN)
			return -EINVAL;

		if (elk->base.duplex != DUPLEX_FULL)
			return -EINVAL;

		if (usb_speed != USB_SPEED_SUPER && speed > SPEED_1000)
			return -EINVAL;

		aqc111_data->autoneg = AUTONEG_DISABLE;
		if (speed != SPEED_UNKNOWN)
			aqc111_data->advertised_speed = speed;

		aqc111_set_phy_speed(dev, aqc111_data->autoneg,
				     aqc111_data->advertised_speed);
	}

	return 0;
}