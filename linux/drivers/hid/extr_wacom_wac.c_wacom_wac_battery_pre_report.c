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
struct hid_report {int dummy; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void wacom_wac_battery_pre_report(struct hid_device *hdev,
		struct hid_report *report)
{
	return;
}