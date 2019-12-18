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
struct cxl {int perst_loads_image; int perst_select_user; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int cxl_update_image_control (struct cxl*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 struct cxl* to_cxl_adapter (struct device*) ; 

__attribute__((used)) static ssize_t load_image_on_perst_store(struct device *device,
				 struct device_attribute *attr,
				 const char *buf, size_t count)
{
	struct cxl *adapter = to_cxl_adapter(device);
	int rc;

	if (!strncmp(buf, "none", 4))
		adapter->perst_loads_image = false;
	else if (!strncmp(buf, "user", 4)) {
		adapter->perst_select_user = true;
		adapter->perst_loads_image = true;
	} else if (!strncmp(buf, "factory", 7)) {
		adapter->perst_select_user = false;
		adapter->perst_loads_image = true;
	} else
		return -EINVAL;

	if ((rc = cxl_update_image_control(adapter)))
		return rc;

	return count;
}