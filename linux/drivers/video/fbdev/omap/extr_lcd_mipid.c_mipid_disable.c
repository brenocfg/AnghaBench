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
struct mipid_device {int /*<<< orphan*/  mutex; scalar_t__ enabled; int /*<<< orphan*/  saved_bklight_level; } ;
struct lcd_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mipid_esd_stop_check (struct mipid_device*) ; 
 int /*<<< orphan*/  mipid_get_bklight_level (struct lcd_panel*) ; 
 int /*<<< orphan*/  mipid_set_bklight_level (struct lcd_panel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_display_state (struct mipid_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sleep_mode (struct mipid_device*,int) ; 
 struct mipid_device* to_mipid_device (struct lcd_panel*) ; 

__attribute__((used)) static void mipid_disable(struct lcd_panel *panel)
{
	struct mipid_device *md = to_mipid_device(panel);

	/*
	 * A final ESD work might be called before returning,
	 * so do this without holding the lock.
	 */
	mipid_esd_stop_check(md);
	mutex_lock(&md->mutex);

	if (!md->enabled) {
		mutex_unlock(&md->mutex);
		return;
	}
	md->saved_bklight_level = mipid_get_bklight_level(panel);
	mipid_set_bklight_level(panel, 0);
	set_display_state(md, 0);
	set_sleep_mode(md, 1);
	md->enabled = 0;

	mutex_unlock(&md->mutex);
}