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
struct nvdimm {int /*<<< orphan*/  dev; } ;
struct nd_mapping {struct nvdimm* nvdimm; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct nvdimm_drvdata* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_nvdimm_bus_locked (int /*<<< orphan*/ *) ; 

struct nvdimm_drvdata *to_ndd(struct nd_mapping *nd_mapping)
{
	struct nvdimm *nvdimm = nd_mapping->nvdimm;

	WARN_ON_ONCE(!is_nvdimm_bus_locked(&nvdimm->dev));

	return dev_get_drvdata(&nvdimm->dev);
}