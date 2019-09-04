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
struct hid_report {int id; struct hid_field** field; } ;
struct hid_field {TYPE_1__* hidinput; } ;
struct hid_device {int claimed; } ;
struct TYPE_2__ {scalar_t__ input; } ;

/* Variables and functions */
 int HID_CLAIMED_INPUT ; 
#define  RMI_ATTN_REPORT_ID 129 
#define  RMI_READ_DATA_REPORT_ID 128 
 int /*<<< orphan*/  input_sync (scalar_t__) ; 

__attribute__((used)) static void rmi_report(struct hid_device *hid, struct hid_report *report)
{
	struct hid_field *field = report->field[0];

	if (!(hid->claimed & HID_CLAIMED_INPUT))
		return;

	switch (report->id) {
	case RMI_READ_DATA_REPORT_ID:
		/* fall-through */
	case RMI_ATTN_REPORT_ID:
		return;
	}

	if (field && field->hidinput && field->hidinput->input)
		input_sync(field->hidinput->input);
}