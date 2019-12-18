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
struct TYPE_2__ {unsigned int value; int /*<<< orphan*/  code; } ;
struct key_entry {int type; TYPE_1__ sw; int /*<<< orphan*/  keycode; int /*<<< orphan*/  code; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_MSC ; 
#define  KE_KEY 130 
#define  KE_SW 129 
#define  KE_VSW 128 
 int /*<<< orphan*/  MSC_SCAN ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  input_report_switch (struct input_dev*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

void sparse_keymap_report_entry(struct input_dev *dev, const struct key_entry *ke,
				unsigned int value, bool autorelease)
{
	switch (ke->type) {
	case KE_KEY:
		input_event(dev, EV_MSC, MSC_SCAN, ke->code);
		input_report_key(dev, ke->keycode, value);
		input_sync(dev);
		if (value && autorelease) {
			input_report_key(dev, ke->keycode, 0);
			input_sync(dev);
		}
		break;

	case KE_SW:
		value = ke->sw.value;
		/* fall through */

	case KE_VSW:
		input_report_switch(dev, ke->sw.code, value);
		input_sync(dev);
		break;
	}
}