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
struct ocxl_afu {int /*<<< orphan*/  pasid_max; int /*<<< orphan*/  pasid_count; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ocxl_afu* to_afu (struct device*) ; 

__attribute__((used)) static ssize_t contexts_show(struct device *device,
		struct device_attribute *attr,
		char *buf)
{
	struct ocxl_afu *afu = to_afu(device);

	return scnprintf(buf, PAGE_SIZE, "%d/%d\n",
			afu->pasid_count, afu->pasid_max);
}