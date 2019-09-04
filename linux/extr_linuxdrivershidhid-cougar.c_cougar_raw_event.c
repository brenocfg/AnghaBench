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
typedef  unsigned char u8 ;
struct hid_report {int dummy; } ;
struct hid_device {int dummy; } ;
struct cougar {TYPE_1__* shared; int /*<<< orphan*/  special_intf; } ;
struct TYPE_2__ {int /*<<< orphan*/  input; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 size_t COUGAR_FIELD_ACTION ; 
 size_t COUGAR_FIELD_CODE ; 
 int /*<<< orphan*/  EV_KEY ; 
 char** cougar_mapping ; 
 struct cougar* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  hid_warn (struct hid_device*,char*,unsigned char) ; 
 int /*<<< orphan*/  input_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char,unsigned char) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cougar_raw_event(struct hid_device *hdev, struct hid_report *report,
			    u8 *data, int size)
{
	struct cougar *cougar;
	unsigned char code, action;
	int i;

	cougar = hid_get_drvdata(hdev);
	if (!cougar->special_intf || !cougar->shared ||
	    !cougar->shared->input || !cougar->shared->enabled)
		return 0;

	code = data[COUGAR_FIELD_CODE];
	action = data[COUGAR_FIELD_ACTION];
	for (i = 0; cougar_mapping[i][0]; i++) {
		if (code == cougar_mapping[i][0]) {
			input_event(cougar->shared->input, EV_KEY,
				    cougar_mapping[i][1], action);
			input_sync(cougar->shared->input);
			return 0;
		}
	}
	hid_warn(hdev, "unmapped special key code %x: ignoring\n", code);
	return 0;
}