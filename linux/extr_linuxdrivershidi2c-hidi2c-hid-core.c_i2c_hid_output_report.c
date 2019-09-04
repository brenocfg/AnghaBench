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
struct hid_device {int dummy; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  HID_OUTPUT_REPORT ; 
 int i2c_hid_output_raw_report (struct hid_device*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int i2c_hid_output_report(struct hid_device *hid, __u8 *buf,
		size_t count)
{
	return i2c_hid_output_raw_report(hid, buf, count, HID_OUTPUT_REPORT,
			false);
}