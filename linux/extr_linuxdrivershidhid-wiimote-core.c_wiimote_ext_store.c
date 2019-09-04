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
struct wiimote_data {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct wiimote_data* dev_to_wii (struct device*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strnlen (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiimote_schedule (struct wiimote_data*) ; 

__attribute__((used)) static ssize_t wiimote_ext_store(struct device *dev,
				 struct device_attribute *attr,
				 const char *buf, size_t count)
{
	struct wiimote_data *wdata = dev_to_wii(dev);

	if (!strcmp(buf, "scan")) {
		wiimote_schedule(wdata);
	} else {
		return -EINVAL;
	}

	return strnlen(buf, PAGE_SIZE);
}