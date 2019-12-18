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
struct mipid_device {int dummy; } ;

/* Variables and functions */
 int MIPID_CMD_SLEEP_IN ; 
 int MIPID_CMD_SLEEP_OUT ; 
 int /*<<< orphan*/  hw_guard_start (struct mipid_device*,int) ; 
 int /*<<< orphan*/  hw_guard_wait (struct mipid_device*) ; 
 int /*<<< orphan*/  mipid_cmd (struct mipid_device*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void set_sleep_mode(struct mipid_device *md, int on)
{
	int cmd, sleep_time = 50;

	if (on)
		cmd = MIPID_CMD_SLEEP_IN;
	else
		cmd = MIPID_CMD_SLEEP_OUT;
	hw_guard_wait(md);
	mipid_cmd(md, cmd);
	hw_guard_start(md, 120);
	/*
	 * When we enable the panel, it seems we _have_ to sleep
	 * 120 ms before sending the init string. When disabling the
	 * panel we'll sleep for the duration of 2 frames, so that the
	 * controller can still provide the PCLK,HS,VS signals.
	 */
	if (!on)
		sleep_time = 120;
	msleep(sleep_time);
}