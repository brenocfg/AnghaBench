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
struct hid_usage {int hid; } ;
struct hid_field {int dummy; } ;
struct hid_device {int dummy; } ;
struct corsair_drvdata {TYPE_2__* k90; } ;
typedef  int /*<<< orphan*/  __s32 ;
struct TYPE_3__ {int brightness; } ;
struct TYPE_4__ {TYPE_1__ record_led; } ;

/* Variables and functions */
#define  CORSAIR_USAGE_MACRO_RECORD_START 129 
#define  CORSAIR_USAGE_MACRO_RECORD_STOP 128 
 int HID_USAGE ; 
 struct corsair_drvdata* hid_get_drvdata (struct hid_device*) ; 

__attribute__((used)) static int corsair_event(struct hid_device *dev, struct hid_field *field,
			 struct hid_usage *usage, __s32 value)
{
	struct corsair_drvdata *drvdata = hid_get_drvdata(dev);

	if (!drvdata->k90)
		return 0;

	switch (usage->hid & HID_USAGE) {
	case CORSAIR_USAGE_MACRO_RECORD_START:
		drvdata->k90->record_led.brightness = 1;
		break;
	case CORSAIR_USAGE_MACRO_RECORD_STOP:
		drvdata->k90->record_led.brightness = 0;
		break;
	default:
		break;
	}

	return 0;
}