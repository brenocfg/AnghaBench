#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int dummy; } ;
struct usb_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct mt76x02_dev {TYPE_1__ mt76; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT76_REMOVED ; 
 int /*<<< orphan*/  ieee80211_free_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ieee80211_unregister_hw (struct ieee80211_hw*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 struct ieee80211_hw* mt76_hw (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x2u_cleanup (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mt76x02_dev* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_put_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mt76x2u_disconnect(struct usb_interface *intf)
{
	struct usb_device *udev = interface_to_usbdev(intf);
	struct mt76x02_dev *dev = usb_get_intfdata(intf);
	struct ieee80211_hw *hw = mt76_hw(dev);

	set_bit(MT76_REMOVED, &dev->mt76.state);
	ieee80211_unregister_hw(hw);
	mt76x2u_cleanup(dev);

	ieee80211_free_hw(hw);
	usb_set_intfdata(intf, NULL);
	usb_put_dev(udev);
}