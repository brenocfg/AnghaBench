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
struct cacheinfo {int type; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
#define  CACHE_TYPE_DATA 130 
#define  CACHE_TYPE_INST 129 
#define  CACHE_TYPE_UNIFIED 128 
 int /*<<< orphan*/  EINVAL ; 
 struct cacheinfo* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static ssize_t type_show(struct device *dev,
			 struct device_attribute *attr, char *buf)
{
	struct cacheinfo *this_leaf = dev_get_drvdata(dev);

	switch (this_leaf->type) {
	case CACHE_TYPE_DATA:
		return sprintf(buf, "Data\n");
	case CACHE_TYPE_INST:
		return sprintf(buf, "Instruction\n");
	case CACHE_TYPE_UNIFIED:
		return sprintf(buf, "Unified\n");
	default:
		return -EINVAL;
	}
}