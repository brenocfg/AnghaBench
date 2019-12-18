#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct resource {scalar_t__ end; scalar_t__ start; } ;
struct nd_region_data {int ns_active; int ns_count; } ;
struct TYPE_4__ {int /*<<< orphan*/  sd; } ;
struct TYPE_5__ {TYPE_1__ kobj; } ;
struct nd_region {scalar_t__ num_lanes; int /*<<< orphan*/  dax_seed; int /*<<< orphan*/  pfn_seed; int /*<<< orphan*/  btt_seed; int /*<<< orphan*/  bb; scalar_t__ ndr_size; scalar_t__ ndr_start; TYPE_2__ dev; int /*<<< orphan*/  bb_state; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,char*) ; 
 struct nd_region_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 scalar_t__ devm_init_badblocks (struct device*,int /*<<< orphan*/ *) ; 
 scalar_t__ is_memory (TYPE_2__*) ; 
 int nd_blk_region_init (struct nd_region*) ; 
 int /*<<< orphan*/  nd_btt_create (struct nd_region*) ; 
 int /*<<< orphan*/  nd_dax_create (struct nd_region*) ; 
 int /*<<< orphan*/  nd_pfn_create (struct nd_region*) ; 
 int nd_region_activate (struct nd_region*) ; 
 int nd_region_register_namespaces (struct nd_region*,int*) ; 
 scalar_t__ num_online_cpus () ; 
 scalar_t__ num_possible_cpus () ; 
 int /*<<< orphan*/  nvdimm_badblocks_populate (struct nd_region*,int /*<<< orphan*/ *,struct resource*) ; 
 int /*<<< orphan*/  sysfs_get_dirent (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 struct nd_region* to_nd_region (struct device*) ; 

__attribute__((used)) static int nd_region_probe(struct device *dev)
{
	int err, rc;
	static unsigned long once;
	struct nd_region_data *ndrd;
	struct nd_region *nd_region = to_nd_region(dev);

	if (nd_region->num_lanes > num_online_cpus()
			&& nd_region->num_lanes < num_possible_cpus()
			&& !test_and_set_bit(0, &once)) {
		dev_dbg(dev, "online cpus (%d) < concurrent i/o lanes (%d) < possible cpus (%d)\n",
				num_online_cpus(), nd_region->num_lanes,
				num_possible_cpus());
		dev_dbg(dev, "setting nr_cpus=%d may yield better libnvdimm device performance\n",
				nd_region->num_lanes);
	}

	rc = nd_region_activate(nd_region);
	if (rc)
		return rc;

	rc = nd_blk_region_init(nd_region);
	if (rc)
		return rc;

	if (is_memory(&nd_region->dev)) {
		struct resource ndr_res;

		if (devm_init_badblocks(dev, &nd_region->bb))
			return -ENODEV;
		nd_region->bb_state = sysfs_get_dirent(nd_region->dev.kobj.sd,
						       "badblocks");
		if (!nd_region->bb_state)
			dev_warn(&nd_region->dev,
					"'badblocks' notification disabled\n");
		ndr_res.start = nd_region->ndr_start;
		ndr_res.end = nd_region->ndr_start + nd_region->ndr_size - 1;
		nvdimm_badblocks_populate(nd_region, &nd_region->bb, &ndr_res);
	}

	rc = nd_region_register_namespaces(nd_region, &err);
	if (rc < 0)
		return rc;

	ndrd = dev_get_drvdata(dev);
	ndrd->ns_active = rc;
	ndrd->ns_count = rc + err;

	if (rc && err && rc == err)
		return -ENODEV;

	nd_region->btt_seed = nd_btt_create(nd_region);
	nd_region->pfn_seed = nd_pfn_create(nd_region);
	nd_region->dax_seed = nd_dax_create(nd_region);
	if (err == 0)
		return 0;

	/*
	 * Given multiple namespaces per region, we do not want to
	 * disable all the successfully registered peer namespaces upon
	 * a single registration failure.  If userspace is missing a
	 * namespace that it expects it can disable/re-enable the region
	 * to retry discovery after correcting the failure.
	 * <regionX>/namespaces returns the current
	 * "<async-registered>/<total>" namespace count.
	 */
	dev_err(dev, "failed to register %d namespace%s, continuing...\n",
			err, err == 1 ? "" : "s");
	return 0;
}