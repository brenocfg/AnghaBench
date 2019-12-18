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
struct device {int dummy; } ;
struct rproc {char* firmware; int max_notifyid; int /*<<< orphan*/ * table_ptr; int /*<<< orphan*/ * cached_table; scalar_t__ nb_vdev; int /*<<< orphan*/  bootaddr; struct device dev; } ;
struct firmware {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int rproc_alloc_registered_carveouts (struct rproc*) ; 
 int /*<<< orphan*/  rproc_disable_iommu (struct rproc*) ; 
 int rproc_enable_iommu (struct rproc*) ; 
 int rproc_fw_sanity_check (struct rproc*,struct firmware const*) ; 
 int /*<<< orphan*/  rproc_get_boot_addr (struct rproc*,struct firmware const*) ; 
 int rproc_handle_resources (struct rproc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rproc_loading_handlers ; 
 int rproc_parse_fw (struct rproc*,struct firmware const*) ; 
 int /*<<< orphan*/  rproc_resource_cleanup (struct rproc*) ; 
 int rproc_start (struct rproc*,struct firmware const*) ; 

__attribute__((used)) static int rproc_fw_boot(struct rproc *rproc, const struct firmware *fw)
{
	struct device *dev = &rproc->dev;
	const char *name = rproc->firmware;
	int ret;

	ret = rproc_fw_sanity_check(rproc, fw);
	if (ret)
		return ret;

	dev_info(dev, "Booting fw image %s, size %zd\n", name, fw->size);

	/*
	 * if enabling an IOMMU isn't relevant for this rproc, this is
	 * just a nop
	 */
	ret = rproc_enable_iommu(rproc);
	if (ret) {
		dev_err(dev, "can't enable iommu: %d\n", ret);
		return ret;
	}

	rproc->bootaddr = rproc_get_boot_addr(rproc, fw);

	/* Load resource table, core dump segment list etc from the firmware */
	ret = rproc_parse_fw(rproc, fw);
	if (ret)
		goto disable_iommu;

	/* reset max_notifyid */
	rproc->max_notifyid = -1;

	/* reset handled vdev */
	rproc->nb_vdev = 0;

	/* handle fw resources which are required to boot rproc */
	ret = rproc_handle_resources(rproc, rproc_loading_handlers);
	if (ret) {
		dev_err(dev, "Failed to process resources: %d\n", ret);
		goto clean_up_resources;
	}

	/* Allocate carveout resources associated to rproc */
	ret = rproc_alloc_registered_carveouts(rproc);
	if (ret) {
		dev_err(dev, "Failed to allocate associated carveouts: %d\n",
			ret);
		goto clean_up_resources;
	}

	ret = rproc_start(rproc, fw);
	if (ret)
		goto clean_up_resources;

	return 0;

clean_up_resources:
	rproc_resource_cleanup(rproc);
	kfree(rproc->cached_table);
	rproc->cached_table = NULL;
	rproc->table_ptr = NULL;
disable_iommu:
	rproc_disable_iommu(rproc);
	return ret;
}