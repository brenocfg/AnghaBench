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
typedef  size_t ssize_t ;
typedef  enum prefault_modes { ____Placeholder_prefault_modes } prefault_modes ;

/* Variables and functions */
 int CXL_PREFAULT_ALL ; 
 int CXL_PREFAULT_NONE ; 
 int CXL_PREFAULT_WED ; 
 size_t EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  radix_enabled () ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 struct cxl_afu* to_cxl_afu (struct device*) ; 

__attribute__((used)) static ssize_t prefault_mode_store(struct device *device,
			  struct device_attribute *attr,
			  const char *buf, size_t count)
{
	struct cxl_afu *afu = to_cxl_afu(device);
	enum prefault_modes mode = -1;

	if (!strncmp(buf, "none", 4))
		mode = CXL_PREFAULT_NONE;
	else {
		if (!radix_enabled()) {

			/* only allowed when not in radix mode */
			if (!strncmp(buf, "work_element_descriptor", 23))
				mode = CXL_PREFAULT_WED;
			if (!strncmp(buf, "all", 3))
				mode = CXL_PREFAULT_ALL;
		} else {
			dev_err(device, "Cannot prefault with radix enabled\n");
		}
	}

	if (mode == -1)
		return -EINVAL;

	afu->prefault_mode = mode;
	return count;
}