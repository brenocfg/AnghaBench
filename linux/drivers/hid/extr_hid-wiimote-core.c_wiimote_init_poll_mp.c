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
struct TYPE_2__ {scalar_t__ mp; } ;
struct wiimote_data {int /*<<< orphan*/  timer; TYPE_1__ state; int /*<<< orphan*/  hdev; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  hid_info (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  wiimote_cmd_acquire_noint (struct wiimote_data*) ; 
 int /*<<< orphan*/  wiimote_cmd_init_mp (struct wiimote_data*) ; 
 int wiimote_cmd_read_mp (struct wiimote_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiimote_cmd_release (struct wiimote_data*) ; 
 int /*<<< orphan*/  wiimote_mp_load (struct wiimote_data*) ; 
 int /*<<< orphan*/  wiimote_mp_unload (struct wiimote_data*) ; 

__attribute__((used)) static void wiimote_init_poll_mp(struct wiimote_data *wdata)
{
	bool mp;
	__u8 mpdata[6];

	wiimote_cmd_acquire_noint(wdata);
	wiimote_cmd_init_mp(wdata);
	mp = wiimote_cmd_read_mp(wdata, mpdata);
	wiimote_cmd_release(wdata);

	/* load/unload MP module if it changed */
	if (mp) {
		if (!wdata->state.mp) {
			hid_info(wdata->hdev, "detected extension: Nintendo Wii Motion Plus\n");
			wiimote_mp_load(wdata);
		}
	} else if (wdata->state.mp) {
		wiimote_mp_unload(wdata);
	}

	mod_timer(&wdata->timer, jiffies + HZ * 4);
}