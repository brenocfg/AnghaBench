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
struct psmouse {int pktsize; int /*<<< orphan*/ * pt_deactivate; int /*<<< orphan*/ * pt_activate; int /*<<< orphan*/ * cleanup; int /*<<< orphan*/ * disconnect; int /*<<< orphan*/ * fast_reconnect; int /*<<< orphan*/ * reconnect; int /*<<< orphan*/  protocol_handler; int /*<<< orphan*/  poll; int /*<<< orphan*/  set_scale; int /*<<< orphan*/  set_resolution; int /*<<< orphan*/  set_rate; int /*<<< orphan*/ * protocol; struct input_dev* dev; } ;
struct input_dev {int /*<<< orphan*/  propbit; int /*<<< orphan*/  mscbit; int /*<<< orphan*/  absbit; int /*<<< orphan*/  relbit; int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_CNT ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  EV_CNT ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_REL ; 
 int /*<<< orphan*/  INPUT_PROP_POINTER ; 
 int /*<<< orphan*/  KEY_CNT ; 
 int /*<<< orphan*/  MSC_CNT ; 
 int /*<<< orphan*/  REL_CNT ; 
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psmouse_poll ; 
 int /*<<< orphan*/  psmouse_process_byte ; 
 int /*<<< orphan*/ * psmouse_protocols ; 
 int /*<<< orphan*/  psmouse_set_rate ; 
 int /*<<< orphan*/  psmouse_set_resolution ; 
 int /*<<< orphan*/  psmouse_set_scale ; 

__attribute__((used)) static void psmouse_apply_defaults(struct psmouse *psmouse)
{
	struct input_dev *input_dev = psmouse->dev;

	bitmap_zero(input_dev->evbit, EV_CNT);
	bitmap_zero(input_dev->keybit, KEY_CNT);
	bitmap_zero(input_dev->relbit, REL_CNT);
	bitmap_zero(input_dev->absbit, ABS_CNT);
	bitmap_zero(input_dev->mscbit, MSC_CNT);

	input_set_capability(input_dev, EV_KEY, BTN_LEFT);
	input_set_capability(input_dev, EV_KEY, BTN_RIGHT);

	input_set_capability(input_dev, EV_REL, REL_X);
	input_set_capability(input_dev, EV_REL, REL_Y);

	__set_bit(INPUT_PROP_POINTER, input_dev->propbit);

	psmouse->protocol = &psmouse_protocols[0];

	psmouse->set_rate = psmouse_set_rate;
	psmouse->set_resolution = psmouse_set_resolution;
	psmouse->set_scale = psmouse_set_scale;
	psmouse->poll = psmouse_poll;
	psmouse->protocol_handler = psmouse_process_byte;
	psmouse->pktsize = 3;
	psmouse->reconnect = NULL;
	psmouse->fast_reconnect = NULL;
	psmouse->disconnect = NULL;
	psmouse->cleanup = NULL;
	psmouse->pt_activate = NULL;
	psmouse->pt_deactivate = NULL;
}