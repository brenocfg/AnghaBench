#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct rt2x00lib_conf {TYPE_1__* conf; } ;
struct rt2x00_dev {int beacon_int; TYPE_3__* ops; } ;
typedef  enum dev_state { ____Placeholder_dev_state } dev_state ;
struct TYPE_6__ {TYPE_2__* lib; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* set_device_state ) (struct rt2x00_dev*,int) ;} ;
struct TYPE_4__ {int flags; int listen_interval; } ;

/* Variables and functions */
 int IEEE80211_CONF_PS ; 
 int /*<<< orphan*/  MAC_CSR18 ; 
 int /*<<< orphan*/  MAC_CSR18_AUTO_WAKE ; 
 int /*<<< orphan*/  MAC_CSR18_BEACONS_BEFORE_WAKEUP ; 
 int /*<<< orphan*/  MAC_CSR18_DELAY_AFTER_BEACON ; 
 int STATE_AWAKE ; 
 int STATE_SLEEP ; 
 int /*<<< orphan*/  rt2500usb_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2500usb_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct rt2x00_dev*,int) ; 

__attribute__((used)) static void rt2500usb_config_ps(struct rt2x00_dev *rt2x00dev,
				struct rt2x00lib_conf *libconf)
{
	enum dev_state state =
	    (libconf->conf->flags & IEEE80211_CONF_PS) ?
		STATE_SLEEP : STATE_AWAKE;
	u16 reg;

	if (state == STATE_SLEEP) {
		reg = rt2500usb_register_read(rt2x00dev, MAC_CSR18);
		rt2x00_set_field16(&reg, MAC_CSR18_DELAY_AFTER_BEACON,
				   rt2x00dev->beacon_int - 20);
		rt2x00_set_field16(&reg, MAC_CSR18_BEACONS_BEFORE_WAKEUP,
				   libconf->conf->listen_interval - 1);

		/* We must first disable autowake before it can be enabled */
		rt2x00_set_field16(&reg, MAC_CSR18_AUTO_WAKE, 0);
		rt2500usb_register_write(rt2x00dev, MAC_CSR18, reg);

		rt2x00_set_field16(&reg, MAC_CSR18_AUTO_WAKE, 1);
		rt2500usb_register_write(rt2x00dev, MAC_CSR18, reg);
	} else {
		reg = rt2500usb_register_read(rt2x00dev, MAC_CSR18);
		rt2x00_set_field16(&reg, MAC_CSR18_AUTO_WAKE, 0);
		rt2500usb_register_write(rt2x00dev, MAC_CSR18, reg);
	}

	rt2x00dev->ops->lib->set_device_state(rt2x00dev, state);
}