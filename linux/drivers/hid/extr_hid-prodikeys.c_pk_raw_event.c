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
struct pk_device {TYPE_1__* pm; } ;
struct hid_report {int id; } ;
struct hid_device {int dummy; } ;
struct TYPE_2__ {int ifnum; } ;

/* Variables and functions */
 struct pk_device* hid_get_drvdata (struct hid_device*) ; 
 int pcmidi_handle_report (TYPE_1__*,int,int*,int) ; 

__attribute__((used)) static int pk_raw_event(struct hid_device *hdev, struct hid_report *report,
	u8 *data, int size)
{
	struct pk_device *pk = hid_get_drvdata(hdev);
	int ret = 0;

	if (1 == pk->pm->ifnum) {
		if (report->id == data[0])
			switch (report->id) {
			case 0x01: /* midi keys (qwerty)*/
			case 0x03: /* midi keyboard (musical)*/
			case 0x04: /* extra/midi keys (qwerty)*/
				ret = pcmidi_handle_report(pk->pm,
						report->id, data, size);
				break;
			}
	}

	return ret;
}