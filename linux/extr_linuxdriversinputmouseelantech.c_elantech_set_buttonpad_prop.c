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
struct psmouse {struct elantech_data* private; struct input_dev* dev; } ;
struct input_dev {int /*<<< orphan*/  keybit; int /*<<< orphan*/  propbit; } ;
struct TYPE_2__ {int fw_version; } ;
struct elantech_data {TYPE_1__ info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  INPUT_PROP_BUTTONPAD ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void elantech_set_buttonpad_prop(struct psmouse *psmouse)
{
	struct input_dev *dev = psmouse->dev;
	struct elantech_data *etd = psmouse->private;

	if (etd->info.fw_version & 0x001000) {
		__set_bit(INPUT_PROP_BUTTONPAD, dev->propbit);
		__clear_bit(BTN_RIGHT, dev->keybit);
	}
}