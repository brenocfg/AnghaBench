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
struct rt2x00_dev {int /*<<< orphan*/  flags; scalar_t__ intf_associated; scalar_t__ intf_sta_count; scalar_t__ intf_ap_count; TYPE_2__* ops; } ;
struct TYPE_4__ {TYPE_1__* lib; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* pre_reset_hw ) (struct rt2x00_dev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_STATE_RESET ; 
 int /*<<< orphan*/  DEVICE_STATE_STARTED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rt2x00lib_enable_radio (struct rt2x00_dev*) ; 
 int rt2x00lib_initialize (struct rt2x00_dev*) ; 
 int rt2x00lib_load_firmware (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00lib_stop (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct rt2x00_dev*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int rt2x00lib_start(struct rt2x00_dev *rt2x00dev)
{
	int retval = 0;

	if (test_bit(DEVICE_STATE_STARTED, &rt2x00dev->flags)) {
		/*
		 * This is special case for ieee80211_restart_hw(), otherwise
		 * mac80211 never call start() two times in row without stop();
		 */
		set_bit(DEVICE_STATE_RESET, &rt2x00dev->flags);
		rt2x00dev->ops->lib->pre_reset_hw(rt2x00dev);
		rt2x00lib_stop(rt2x00dev);
	}

	/*
	 * If this is the first interface which is added,
	 * we should load the firmware now.
	 */
	retval = rt2x00lib_load_firmware(rt2x00dev);
	if (retval)
		goto out;

	/*
	 * Initialize the device.
	 */
	retval = rt2x00lib_initialize(rt2x00dev);
	if (retval)
		goto out;

	rt2x00dev->intf_ap_count = 0;
	rt2x00dev->intf_sta_count = 0;
	rt2x00dev->intf_associated = 0;

	/* Enable the radio */
	retval = rt2x00lib_enable_radio(rt2x00dev);
	if (retval)
		goto out;

	set_bit(DEVICE_STATE_STARTED, &rt2x00dev->flags);

out:
	clear_bit(DEVICE_STATE_RESET, &rt2x00dev->flags);
	return retval;
}