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
struct dimm_info {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  edac_dimm_info_location (struct dimm_info*,char*,int /*<<< orphan*/ ) ; 
 struct dimm_info* to_dimm (struct device*) ; 

__attribute__((used)) static ssize_t dimmdev_location_show(struct device *dev,
				     struct device_attribute *mattr, char *data)
{
	struct dimm_info *dimm = to_dimm(dev);

	return edac_dimm_info_location(dimm, data, PAGE_SIZE);
}