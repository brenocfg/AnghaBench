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
struct cxl {scalar_t__ user_image_loaded; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*) ; 
 struct cxl* to_cxl_adapter (struct device*) ; 

__attribute__((used)) static ssize_t image_loaded_show(struct device *device,
				 struct device_attribute *attr,
				 char *buf)
{
	struct cxl *adapter = to_cxl_adapter(device);

	if (adapter->user_image_loaded)
		return scnprintf(buf, PAGE_SIZE, "user\n");
	return scnprintf(buf, PAGE_SIZE, "factory\n");
}