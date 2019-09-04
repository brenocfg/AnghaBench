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
struct notifier_block {int dummy; } ;
struct TYPE_4__ {TYPE_1__* input; } ;
struct TYPE_3__ {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
#define  ADB_MSG_POST_RESET 130 
#define  ADB_MSG_POWERDOWN 129 
#define  ADB_MSG_PRE_RESET 128 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  adb_poll () ; 
 TYPE_2__** adbhid ; 
 int /*<<< orphan*/  adbhid_kbd_capslock_remember () ; 
 int /*<<< orphan*/  adbhid_probe () ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  leds_req_pending ; 
 int /*<<< orphan*/  restore_capslock_events ; 

__attribute__((used)) static int
adb_message_handler(struct notifier_block *this, unsigned long code, void *x)
{
	switch (code) {
	case ADB_MSG_PRE_RESET:
	case ADB_MSG_POWERDOWN:
		/* Stop the repeat timer. Autopoll is already off at this point */
		{
			int i;
			for (i = 1; i < 16; i++) {
				if (adbhid[i])
					del_timer_sync(&adbhid[i]->input->timer);
			}
		}

		/* Stop pending led requests */
		while (leds_req_pending)
			adb_poll();

		/* After resume, and if the capslock LED is on, the PMU will
		 * send a "capslock down" key event. This confuses the
		 * restore_capslock_events logic. Remember if the capslock
		 * LED was on before suspend so the unwanted key event can
		 * be ignored after resume. */
		if (restore_capslock_events)
			adbhid_kbd_capslock_remember();

		break;

	case ADB_MSG_POST_RESET:
		adbhid_probe();
		break;
	}
	return NOTIFY_DONE;
}