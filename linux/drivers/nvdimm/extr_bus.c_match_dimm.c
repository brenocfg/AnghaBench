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
struct nvdimm {long id; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ is_nvdimm (struct device*) ; 
 struct nvdimm* to_nvdimm (struct device*) ; 

__attribute__((used)) static int match_dimm(struct device *dev, void *data)
{
	long id = (long) data;

	if (is_nvdimm(dev)) {
		struct nvdimm *nvdimm = to_nvdimm(dev);

		return nvdimm->id == id;
	}

	return 0;
}