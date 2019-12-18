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
struct pcmidi_snd {struct hid_report* pcmidi_report6; TYPE_1__* pk; } ;
struct hid_report {TYPE_2__** field; } ;
struct hid_device {int dummy; } ;
struct TYPE_4__ {int* value; } ;
struct TYPE_3__ {struct hid_device* hdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HID_REQ_SET_REPORT ; 
 int /*<<< orphan*/  hid_hw_request (struct hid_device*,struct hid_report*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcmidi_submit_output_report(struct pcmidi_snd *pm, int state)
{
	struct hid_device *hdev = pm->pk->hdev;
	struct hid_report *report = pm->pcmidi_report6;
	report->field[0]->value[0] = 0x01;
	report->field[0]->value[1] = state;

	hid_hw_request(hdev, report, HID_REQ_SET_REPORT);
}