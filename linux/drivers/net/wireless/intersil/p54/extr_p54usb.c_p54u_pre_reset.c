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
struct usb_interface {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  p54u_stop (struct ieee80211_hw*) ; 
 struct ieee80211_hw* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int p54u_pre_reset(struct usb_interface *intf)
{
	struct ieee80211_hw *dev = usb_get_intfdata(intf);

	if (!dev)
		return -ENODEV;

	p54u_stop(dev);
	return 0;
}