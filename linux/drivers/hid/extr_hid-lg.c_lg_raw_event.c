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
typedef  int /*<<< orphan*/  u8 ;
struct lg_drv_data {int quirks; } ;
struct hid_report {int dummy; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int LG_FF4 ; 
 struct lg_drv_data* hid_get_drvdata (struct hid_device*) ; 
 int lg4ff_raw_event (struct hid_device*,struct hid_report*,int /*<<< orphan*/ *,int,struct lg_drv_data*) ; 

__attribute__((used)) static int lg_raw_event(struct hid_device *hdev, struct hid_report *report,
		u8 *rd, int size)
{
	struct lg_drv_data *drv_data = hid_get_drvdata(hdev);

	if (drv_data->quirks & LG_FF4)
		return lg4ff_raw_event(hdev, report, rd, size, drv_data);

	return 0;
}