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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct wacom {TYPE_1__ wacom_wac; } ;
struct hid_report {int dummy; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int WACOM_PKGLEN_MAX ; 
 struct wacom* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wacom_wac_irq (TYPE_1__*,int) ; 
 scalar_t__ wacom_wac_pen_serial_enforce (struct hid_device*,struct hid_report*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int wacom_raw_event(struct hid_device *hdev, struct hid_report *report,
		u8 *raw_data, int size)
{
	struct wacom *wacom = hid_get_drvdata(hdev);

	if (size > WACOM_PKGLEN_MAX)
		return 1;

	if (wacom_wac_pen_serial_enforce(hdev, report, raw_data, size))
		return -1;

	memcpy(wacom->wacom_wac.data, raw_data, size);

	wacom_wac_irq(&wacom->wacom_wac, size);

	return 0;
}