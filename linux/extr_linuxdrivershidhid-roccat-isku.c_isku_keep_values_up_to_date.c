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
typedef  int u8 ;
struct isku_report_button {int /*<<< orphan*/  data1; int /*<<< orphan*/  event; } ;
struct isku_device {int dummy; } ;

/* Variables and functions */
#define  ISKU_REPORT_BUTTON_EVENT_PROFILE 129 
#define  ISKU_REPORT_NUMBER_BUTTON 128 
 int /*<<< orphan*/  isku_profile_activated (struct isku_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isku_keep_values_up_to_date(struct isku_device *isku,
		u8 const *data)
{
	struct isku_report_button const *button_report;

	switch (data[0]) {
	case ISKU_REPORT_NUMBER_BUTTON:
		button_report = (struct isku_report_button const *)data;
		switch (button_report->event) {
		case ISKU_REPORT_BUTTON_EVENT_PROFILE:
			isku_profile_activated(isku, button_report->data1 - 1);
			break;
		}
		break;
	}
}