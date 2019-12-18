#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nvdimm_bus {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct nvdimm {TYPE_1__ dev; } ;

/* Variables and functions */
 struct nvdimm_bus* to_nvdimm_bus (int /*<<< orphan*/ ) ; 

struct nvdimm_bus *nvdimm_to_bus(struct nvdimm *nvdimm)
{
	return to_nvdimm_bus(nvdimm->dev.parent);
}