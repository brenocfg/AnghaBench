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
struct synusb {int* data; struct input_dev* input; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_MIDDLE ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void synusb_report_buttons(struct synusb *synusb)
{
	struct input_dev *input_dev = synusb->input;

	input_report_key(input_dev, BTN_LEFT, synusb->data[1] & 0x04);
	input_report_key(input_dev, BTN_RIGHT, synusb->data[1] & 0x01);
	input_report_key(input_dev, BTN_MIDDLE, synusb->data[1] & 0x02);
}