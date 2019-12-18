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
struct input_dev {int /*<<< orphan*/  keybit; } ;

/* Variables and functions */
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 int wacom_numbered_button_to_key (int) ; 

__attribute__((used)) static void wacom_setup_numbered_buttons(struct input_dev *input_dev,
				int button_count)
{
	int i;

	for (i = 0; i < button_count; i++) {
		int key = wacom_numbered_button_to_key(i);

		if (key)
			__set_bit(key, input_dev->keybit);
	}
}