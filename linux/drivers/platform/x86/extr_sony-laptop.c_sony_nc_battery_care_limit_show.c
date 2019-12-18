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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 TYPE_1__* bcare_ctl ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,unsigned int) ; 
 scalar_t__ sony_call_snc_handle (int /*<<< orphan*/ ,int,unsigned int*) ; 

__attribute__((used)) static ssize_t sony_nc_battery_care_limit_show(struct device *dev,
		struct device_attribute *attr, char *buffer)
{
	unsigned int result, status;

	if (sony_call_snc_handle(bcare_ctl->handle, 0x0000, &result))
		return -EIO;

	status = (result & 0x01) ? ((result & 0x30) >> 0x04) : 0;
	switch (status) {
	case 1:
		status = 80;
		break;
	case 2:
		status = 50;
		break;
	case 3:
		status = 100;
		break;
	default:
		status = 0;
		break;
	}

	return snprintf(buffer, PAGE_SIZE, "%d\n", status);
}