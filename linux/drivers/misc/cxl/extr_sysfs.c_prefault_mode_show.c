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
struct cxl_afu {int prefault_mode; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
#define  CXL_PREFAULT_ALL 129 
#define  CXL_PREFAULT_WED 128 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*) ; 
 struct cxl_afu* to_cxl_afu (struct device*) ; 

__attribute__((used)) static ssize_t prefault_mode_show(struct device *device,
				  struct device_attribute *attr,
				  char *buf)
{
	struct cxl_afu *afu = to_cxl_afu(device);

	switch (afu->prefault_mode) {
	case CXL_PREFAULT_WED:
		return scnprintf(buf, PAGE_SIZE, "work_element_descriptor\n");
	case CXL_PREFAULT_ALL:
		return scnprintf(buf, PAGE_SIZE, "all\n");
	default:
		return scnprintf(buf, PAGE_SIZE, "none\n");
	}
}