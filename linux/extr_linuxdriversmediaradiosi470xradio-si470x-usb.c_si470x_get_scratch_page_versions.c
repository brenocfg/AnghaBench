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
struct si470x_device {int /*<<< orphan*/ * usb_buf; int /*<<< orphan*/  hardware_version; int /*<<< orphan*/  software_version; TYPE_1__* intf; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SCRATCH_REPORT ; 
 int /*<<< orphan*/  SCRATCH_REPORT_SIZE ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int si470x_get_report (struct si470x_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si470x_get_scratch_page_versions(struct si470x_device *radio)
{
	int retval;

	radio->usb_buf[0] = SCRATCH_REPORT;

	retval = si470x_get_report(radio, radio->usb_buf, SCRATCH_REPORT_SIZE);

	if (retval < 0)
		dev_warn(&radio->intf->dev, "si470x_get_scratch: si470x_get_report returned %d\n",
			 retval);
	else {
		radio->software_version = radio->usb_buf[1];
		radio->hardware_version = radio->usb_buf[2];
	}

	return (retval < 0) ? -EINVAL : 0;
}