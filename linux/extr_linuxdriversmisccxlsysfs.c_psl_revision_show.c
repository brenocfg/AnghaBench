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
struct cxl {int /*<<< orphan*/  psl_rev; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct cxl* to_cxl_adapter (struct device*) ; 

__attribute__((used)) static ssize_t psl_revision_show(struct device *device,
				 struct device_attribute *attr,
				 char *buf)
{
	struct cxl *adapter = to_cxl_adapter(device);

	return scnprintf(buf, PAGE_SIZE, "%i\n", adapter->psl_rev);
}