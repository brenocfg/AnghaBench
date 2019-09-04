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
struct m560_private_data {struct input_dev* input; } ;
struct input_dev {int /*<<< orphan*/  relbit; int /*<<< orphan*/  evbit; int /*<<< orphan*/  keybit; } ;
struct hidpp_device {struct m560_private_data* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_BACK ; 
 int /*<<< orphan*/  BTN_FORWARD ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_MIDDLE ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_REL ; 
 int /*<<< orphan*/  REL_HWHEEL ; 
 int /*<<< orphan*/  REL_WHEEL ; 
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void m560_populate_input(struct hidpp_device *hidpp,
		struct input_dev *input_dev, bool origin_is_hid_core)
{
	struct m560_private_data *mydata = hidpp->private_data;

	mydata->input = input_dev;

	__set_bit(EV_KEY, mydata->input->evbit);
	__set_bit(BTN_MIDDLE, mydata->input->keybit);
	__set_bit(BTN_RIGHT, mydata->input->keybit);
	__set_bit(BTN_LEFT, mydata->input->keybit);
	__set_bit(BTN_BACK, mydata->input->keybit);
	__set_bit(BTN_FORWARD, mydata->input->keybit);

	__set_bit(EV_REL, mydata->input->evbit);
	__set_bit(REL_X, mydata->input->relbit);
	__set_bit(REL_Y, mydata->input->relbit);
	__set_bit(REL_WHEEL, mydata->input->relbit);
	__set_bit(REL_HWHEEL, mydata->input->relbit);
}