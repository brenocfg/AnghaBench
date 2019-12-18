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
struct adbhid {int flags; int* keycode; int /*<<< orphan*/  input; } ;

/* Variables and functions */
#define  ADB_KEY_CAPSLOCK 135 
 int ADB_KEY_CMD ; 
#define  ADB_KEY_DEL 134 
#define  ADB_KEY_FN 133 
 int ADB_KEY_FWDEL ; 
#define  ADB_KEY_POWER 132 
#define  ADB_KEY_POWER_OLD 131 
 int FLAG_CAPSLOCK_DOWN ; 
 int FLAG_CAPSLOCK_IGNORE_NEXT ; 
 int FLAG_CAPSLOCK_TRANSLATE ; 
 int FLAG_EMU_FWDEL_DOWN ; 
 int FLAG_FN_KEY_PRESSED ; 
 int FLAG_POWER_FROM_FN ; 
 int FLAG_POWER_KEY_PRESSED ; 
 int KEY_CAPSLOCK ; 
 int /*<<< orphan*/  PMAC_FTR_GET_MB_INFO ; 
 int /*<<< orphan*/  PMAC_MB_INFO_MODEL ; 
#define  PMAC_TYPE_COMET 130 
#define  PMAC_TYPE_HOOPER 129 
#define  PMAC_TYPE_KANGA 128 
 struct adbhid** adbhid ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmac_call_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 scalar_t__ restore_capslock_events ; 

__attribute__((used)) static void
adbhid_input_keycode(int id, int scancode, int repeat)
{
	struct adbhid *ahid = adbhid[id];
	int keycode, up_flag, key;

	keycode = scancode & 0x7f;
	up_flag = scancode & 0x80;

	if (restore_capslock_events) {
		if (keycode == ADB_KEY_CAPSLOCK && !up_flag) {
			/* Key pressed, turning on the CapsLock LED.
			 * The next 0xff will be interpreted as a release. */
			if (ahid->flags & FLAG_CAPSLOCK_IGNORE_NEXT) {
				/* Throw away this key event if it happens
				 * just after resume. */
				ahid->flags &= ~FLAG_CAPSLOCK_IGNORE_NEXT;
				return;
			} else {
				ahid->flags |= FLAG_CAPSLOCK_TRANSLATE
					| FLAG_CAPSLOCK_DOWN;
			}
		} else if (scancode == 0xff &&
			   !(ahid->flags & FLAG_POWER_KEY_PRESSED)) {
			/* Scancode 0xff usually signifies that the capslock
			 * key was either pressed or released, or that the
			 * power button was released. */
			if (ahid->flags & FLAG_CAPSLOCK_TRANSLATE) {
				keycode = ADB_KEY_CAPSLOCK;
				if (ahid->flags & FLAG_CAPSLOCK_DOWN) {
					/* Key released */
					up_flag = 1;
					ahid->flags &= ~FLAG_CAPSLOCK_DOWN;
				} else {
					/* Key pressed */
					up_flag = 0;
					ahid->flags &= ~FLAG_CAPSLOCK_TRANSLATE;
				}
			} else {
				pr_info("Spurious caps lock event (scancode 0xff).\n");
			}
		}
	}

	switch (keycode) {
	case ADB_KEY_CAPSLOCK:
		if (!restore_capslock_events) {
			/* Generate down/up events for CapsLock every time. */
			input_report_key(ahid->input, KEY_CAPSLOCK, 1);
			input_sync(ahid->input);
			input_report_key(ahid->input, KEY_CAPSLOCK, 0);
			input_sync(ahid->input);
			return;
		}
		break;
#ifdef CONFIG_PPC_PMAC
	case ADB_KEY_POWER_OLD: /* Power key on PBook 3400 needs remapping */
		switch(pmac_call_feature(PMAC_FTR_GET_MB_INFO,
			NULL, PMAC_MB_INFO_MODEL, 0)) {
		case PMAC_TYPE_COMET:
		case PMAC_TYPE_HOOPER:
		case PMAC_TYPE_KANGA:
			keycode = ADB_KEY_POWER;
		}
		break;
	case ADB_KEY_POWER:
		/* Keep track of the power key state */
		if (up_flag)
			ahid->flags &= ~FLAG_POWER_KEY_PRESSED;
		else
			ahid->flags |= FLAG_POWER_KEY_PRESSED;

		/* Fn + Command will produce a bogus "power" keycode */
		if (ahid->flags & FLAG_FN_KEY_PRESSED) {
			keycode = ADB_KEY_CMD;
			if (up_flag)
				ahid->flags &= ~FLAG_POWER_FROM_FN;
			else
				ahid->flags |= FLAG_POWER_FROM_FN;
		} else if (ahid->flags & FLAG_POWER_FROM_FN) {
			keycode = ADB_KEY_CMD;
			ahid->flags &= ~FLAG_POWER_FROM_FN;
		}
		break;
	case ADB_KEY_FN:
		/* Keep track of the Fn key state */
		if (up_flag) {
			ahid->flags &= ~FLAG_FN_KEY_PRESSED;
			/* Emulate Fn+delete = forward delete */
			if (ahid->flags & FLAG_EMU_FWDEL_DOWN) {
				ahid->flags &= ~FLAG_EMU_FWDEL_DOWN;
				keycode = ADB_KEY_FWDEL;
				break;
			}
		} else
			ahid->flags |= FLAG_FN_KEY_PRESSED;
		break;
	case ADB_KEY_DEL:
		/* Emulate Fn+delete = forward delete */
		if (ahid->flags & FLAG_FN_KEY_PRESSED) {
			keycode = ADB_KEY_FWDEL;
			if (up_flag)
				ahid->flags &= ~FLAG_EMU_FWDEL_DOWN;
			else
				ahid->flags |= FLAG_EMU_FWDEL_DOWN;
		}
		break;
#endif /* CONFIG_PPC_PMAC */
	}

	key = adbhid[id]->keycode[keycode];
	if (key) {
		input_report_key(adbhid[id]->input, key, !up_flag);
		input_sync(adbhid[id]->input);
	} else
		pr_info("Unhandled ADB key (scancode %#02x) %s.\n", keycode,
			up_flag ? "released" : "pressed");

}