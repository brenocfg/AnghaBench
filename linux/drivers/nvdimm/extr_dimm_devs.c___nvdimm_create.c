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
struct resource {int dummy; } ;
struct nvdimm_security_ops {int dummy; } ;
struct nvdimm_bus {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {void* ext_flags; void* flags; scalar_t__ overwrite_tmo; struct nvdimm_security_ops const* ops; } ;
struct device {struct attribute_group const** groups; int /*<<< orphan*/  devt; int /*<<< orphan*/ * type; int /*<<< orphan*/ * parent; } ;
struct nvdimm {scalar_t__ id; char const* dimm_id; unsigned long flags; unsigned long cmd_mask; int num_flush; TYPE_1__ sec; int /*<<< orphan*/  dwork; struct device dev; int /*<<< orphan*/  busy; struct resource* flush_wpq; void* provider_data; } ;
struct attribute_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,scalar_t__) ; 
 int NDD_NOBLK ; 
 int /*<<< orphan*/  NVDIMM_MASTER ; 
 int /*<<< orphan*/  NVDIMM_USER ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_name (struct device*,char*,scalar_t__) ; 
 int /*<<< orphan*/  dimm_ida ; 
 scalar_t__ ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nvdimm*) ; 
 struct nvdimm* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nd_device_register (struct device*) ; 
 scalar_t__ noblk ; 
 int /*<<< orphan*/  nvdimm_device_type ; 
 int /*<<< orphan*/  nvdimm_major ; 
 void* nvdimm_security_flags (struct nvdimm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvdimm_security_overwrite_query ; 

struct nvdimm *__nvdimm_create(struct nvdimm_bus *nvdimm_bus,
		void *provider_data, const struct attribute_group **groups,
		unsigned long flags, unsigned long cmd_mask, int num_flush,
		struct resource *flush_wpq, const char *dimm_id,
		const struct nvdimm_security_ops *sec_ops)
{
	struct nvdimm *nvdimm = kzalloc(sizeof(*nvdimm), GFP_KERNEL);
	struct device *dev;

	if (!nvdimm)
		return NULL;

	nvdimm->id = ida_simple_get(&dimm_ida, 0, 0, GFP_KERNEL);
	if (nvdimm->id < 0) {
		kfree(nvdimm);
		return NULL;
	}

	nvdimm->dimm_id = dimm_id;
	nvdimm->provider_data = provider_data;
	if (noblk)
		flags |= 1 << NDD_NOBLK;
	nvdimm->flags = flags;
	nvdimm->cmd_mask = cmd_mask;
	nvdimm->num_flush = num_flush;
	nvdimm->flush_wpq = flush_wpq;
	atomic_set(&nvdimm->busy, 0);
	dev = &nvdimm->dev;
	dev_set_name(dev, "nmem%d", nvdimm->id);
	dev->parent = &nvdimm_bus->dev;
	dev->type = &nvdimm_device_type;
	dev->devt = MKDEV(nvdimm_major, nvdimm->id);
	dev->groups = groups;
	nvdimm->sec.ops = sec_ops;
	nvdimm->sec.overwrite_tmo = 0;
	INIT_DELAYED_WORK(&nvdimm->dwork, nvdimm_security_overwrite_query);
	/*
	 * Security state must be initialized before device_add() for
	 * attribute visibility.
	 */
	/* get security state and extended (master) state */
	nvdimm->sec.flags = nvdimm_security_flags(nvdimm, NVDIMM_USER);
	nvdimm->sec.ext_flags = nvdimm_security_flags(nvdimm, NVDIMM_MASTER);
	nd_device_register(dev);

	return nvdimm;
}