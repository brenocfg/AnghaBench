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
struct resource {int dummy; } ;
struct nvdimm_drvdata {int /*<<< orphan*/  dpa; int /*<<< orphan*/  dev; } ;
struct nd_label_id {int dummy; } ;
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct resource* __request_region (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_nvdimm_bus_locked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmemdup (struct nd_label_id*,int,int /*<<< orphan*/ ) ; 

struct resource *nvdimm_allocate_dpa(struct nvdimm_drvdata *ndd,
		struct nd_label_id *label_id, resource_size_t start,
		resource_size_t n)
{
	char *name = kmemdup(label_id, sizeof(*label_id), GFP_KERNEL);
	struct resource *res;

	if (!name)
		return NULL;

	WARN_ON_ONCE(!is_nvdimm_bus_locked(ndd->dev));
	res = __request_region(&ndd->dpa, start, n, name, 0);
	if (!res)
		kfree(name);
	return res;
}