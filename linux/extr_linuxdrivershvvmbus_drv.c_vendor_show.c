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
struct hv_device {int vendor_id; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct hv_device* device_to_hv_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t vendor_show(struct device *dev,
			   struct device_attribute *dev_attr,
			   char *buf)
{
	struct hv_device *hv_dev = device_to_hv_device(dev);
	return sprintf(buf, "0x%x\n", hv_dev->vendor_id);
}