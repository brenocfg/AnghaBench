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
struct TYPE_2__ {scalar_t__ inrange_state; } ;
struct wacom_wac {TYPE_1__ hid_data; } ;
struct wacom {struct wacom_wac wacom_wac; } ;
struct hid_report {int dummy; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 struct wacom* hid_get_drvdata (struct hid_device*) ; 

__attribute__((used)) static void wacom_wac_pad_pre_report(struct hid_device *hdev,
		struct hid_report *report)
{
	struct wacom *wacom = hid_get_drvdata(hdev);
	struct wacom_wac *wacom_wac = &wacom->wacom_wac;

	wacom_wac->hid_data.inrange_state = 0;
}