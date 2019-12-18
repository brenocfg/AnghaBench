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
struct wacom_wac {unsigned char* data; int /*<<< orphan*/ * tool; struct input_dev* pad_input; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MISC ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  MSC_SERIAL ; 
 int /*<<< orphan*/  PAD_DEVICE_ID ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  wacom_report_numbered_buttons (struct input_dev*,int,int) ; 

__attribute__((used)) static void wacom_intuos_gen3_bt_pad(struct wacom_wac *wacom)
{
	struct input_dev *pad_input = wacom->pad_input;
	unsigned char *data = wacom->data;

	int buttons = data[44];

	wacom_report_numbered_buttons(pad_input, 4, buttons);

	input_report_key(pad_input, wacom->tool[1], buttons ? 1 : 0);
	input_report_abs(pad_input, ABS_MISC, buttons ? PAD_DEVICE_ID : 0);
	input_event(pad_input, EV_MSC, MSC_SERIAL, 0xffffffff);

	input_sync(pad_input);
}