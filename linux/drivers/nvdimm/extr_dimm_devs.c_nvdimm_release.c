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
struct nvdimm {int /*<<< orphan*/  id; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dimm_ida ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nvdimm*) ; 
 struct nvdimm* to_nvdimm (struct device*) ; 

__attribute__((used)) static void nvdimm_release(struct device *dev)
{
	struct nvdimm *nvdimm = to_nvdimm(dev);

	ida_simple_remove(&dimm_ida, nvdimm->id);
	kfree(nvdimm);
}