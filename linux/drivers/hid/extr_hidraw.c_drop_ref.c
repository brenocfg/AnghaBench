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
struct hidraw {size_t minor; int /*<<< orphan*/  hid; scalar_t__ exist; scalar_t__ open; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  PM_HINT_NORMAL ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_hw_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_hw_power (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hidraw_class ; 
 int /*<<< orphan*/  hidraw_major ; 
 int /*<<< orphan*/ ** hidraw_table ; 
 int /*<<< orphan*/  kfree (struct hidraw*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drop_ref(struct hidraw *hidraw, int exists_bit)
{
	if (exists_bit) {
		hidraw->exist = 0;
		if (hidraw->open) {
			hid_hw_close(hidraw->hid);
			wake_up_interruptible(&hidraw->wait);
		}
		device_destroy(hidraw_class,
			       MKDEV(hidraw_major, hidraw->minor));
	} else {
		--hidraw->open;
	}
	if (!hidraw->open) {
		if (!hidraw->exist) {
			hidraw_table[hidraw->minor] = NULL;
			kfree(hidraw);
		} else {
			/* close device for last reader */
			hid_hw_close(hidraw->hid);
			hid_hw_power(hidraw->hid, PM_HINT_NORMAL);
		}
	}
}