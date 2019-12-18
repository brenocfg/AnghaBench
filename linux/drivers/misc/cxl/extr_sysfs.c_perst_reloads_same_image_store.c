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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct cxl {int perst_same_image; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int sscanf (char const*,char*,int*) ; 
 struct cxl* to_cxl_adapter (struct device*) ; 

__attribute__((used)) static ssize_t perst_reloads_same_image_store(struct device *device,
				 struct device_attribute *attr,
				 const char *buf, size_t count)
{
	struct cxl *adapter = to_cxl_adapter(device);
	int rc;
	int val;

	rc = sscanf(buf, "%i", &val);
	if ((rc != 1) || !(val == 1 || val == 0))
		return -EINVAL;

	adapter->perst_same_image = (val == 1 ? true : false);
	return count;
}