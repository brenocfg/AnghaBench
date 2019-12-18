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
typedef  int u8 ;
struct sony_laptop_keypress {struct input_dev* dev; int /*<<< orphan*/  key; int /*<<< orphan*/ * member_0; } ;
struct input_dev {int dummy; } ;
typedef  int /*<<< orphan*/  kp ;
struct TYPE_2__ {int /*<<< orphan*/  release_key_timer; int /*<<< orphan*/  fifo_lock; int /*<<< orphan*/  fifo; struct input_dev* key_dev; struct input_dev* jog_dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  BTN_MIDDLE ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  KEY_UNKNOWN ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int /*<<< orphan*/  REL_WHEEL ; 
 int SONYPI_EVENT_ANYBUTTON_RELEASED ; 
 int SONYPI_EVENT_FNKEY_RELEASED ; 
#define  SONYPI_EVENT_JOGDIAL_DOWN 132 
#define  SONYPI_EVENT_JOGDIAL_DOWN_PRESSED 131 
#define  SONYPI_EVENT_JOGDIAL_PRESSED 130 
#define  SONYPI_EVENT_JOGDIAL_UP 129 
#define  SONYPI_EVENT_JOGDIAL_UP_PRESSED 128 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_rel (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfifo_in_locked (int /*<<< orphan*/ *,unsigned char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 TYPE_1__ sony_laptop_input ; 
 int* sony_laptop_input_index ; 
 int /*<<< orphan*/ * sony_laptop_input_keycode_map ; 

__attribute__((used)) static void sony_laptop_report_input_event(u8 event)
{
	struct input_dev *jog_dev = sony_laptop_input.jog_dev;
	struct input_dev *key_dev = sony_laptop_input.key_dev;
	struct sony_laptop_keypress kp = { NULL };
	int scancode = -1;

	if (event == SONYPI_EVENT_FNKEY_RELEASED ||
			event == SONYPI_EVENT_ANYBUTTON_RELEASED) {
		/* Nothing, not all VAIOs generate this event */
		return;
	}

	/* report events */
	switch (event) {
	/* jog_dev events */
	case SONYPI_EVENT_JOGDIAL_UP:
	case SONYPI_EVENT_JOGDIAL_UP_PRESSED:
		input_report_rel(jog_dev, REL_WHEEL, 1);
		input_sync(jog_dev);
		return;

	case SONYPI_EVENT_JOGDIAL_DOWN:
	case SONYPI_EVENT_JOGDIAL_DOWN_PRESSED:
		input_report_rel(jog_dev, REL_WHEEL, -1);
		input_sync(jog_dev);
		return;

	/* key_dev events */
	case SONYPI_EVENT_JOGDIAL_PRESSED:
		kp.key = BTN_MIDDLE;
		kp.dev = jog_dev;
		break;

	default:
		if (event >= ARRAY_SIZE(sony_laptop_input_index)) {
			dprintk("sony_laptop_report_input_event, event not known: %d\n", event);
			break;
		}
		if ((scancode = sony_laptop_input_index[event]) != -1) {
			kp.key = sony_laptop_input_keycode_map[scancode];
			if (kp.key != KEY_UNKNOWN)
				kp.dev = key_dev;
		}
		break;
	}

	if (kp.dev) {
		/* if we have a scancode we emit it so we can always
		    remap the key */
		if (scancode != -1)
			input_event(kp.dev, EV_MSC, MSC_SCAN, scancode);
		input_report_key(kp.dev, kp.key, 1);
		input_sync(kp.dev);

		/* schedule key release */
		kfifo_in_locked(&sony_laptop_input.fifo,
				(unsigned char *)&kp, sizeof(kp),
				&sony_laptop_input.fifo_lock);
		mod_timer(&sony_laptop_input.release_key_timer,
			  jiffies + msecs_to_jiffies(10));
	} else
		dprintk("unknown input event %.2x\n", event);
}