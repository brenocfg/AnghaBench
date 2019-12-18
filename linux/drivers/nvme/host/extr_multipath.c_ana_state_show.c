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
struct nvme_ns {size_t ana_state; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 char** nvme_ana_state_names ; 
 struct nvme_ns* nvme_get_ns_from_dev (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t ana_state_show(struct device *dev, struct device_attribute *attr,
		char *buf)
{
	struct nvme_ns *ns = nvme_get_ns_from_dev(dev);

	return sprintf(buf, "%s\n", nvme_ana_state_names[ns->ana_state]);
}