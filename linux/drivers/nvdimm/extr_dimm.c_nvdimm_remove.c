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
struct nvdimm_drvdata {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct nvdimm_drvdata* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvdimm_bus_lock (struct device*) ; 
 int /*<<< orphan*/  nvdimm_bus_unlock (struct device*) ; 
 int /*<<< orphan*/  put_ndd (struct nvdimm_drvdata*) ; 

__attribute__((used)) static int nvdimm_remove(struct device *dev)
{
	struct nvdimm_drvdata *ndd = dev_get_drvdata(dev);

	if (!ndd)
		return 0;

	nvdimm_bus_lock(dev);
	dev_set_drvdata(dev, NULL);
	nvdimm_bus_unlock(dev);
	put_ndd(ndd);

	return 0;
}