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
struct rproc_vring {int notifyid; int /*<<< orphan*/  align; int /*<<< orphan*/  len; } ;
struct rproc_vdev {int rsc_offset; int /*<<< orphan*/  index; struct rproc_vring* vring; struct rproc* rproc; } ;
struct rproc_mem_entry {int dummy; } ;
struct device {int dummy; } ;
struct rproc {int max_notifyid; int /*<<< orphan*/  notifyids; scalar_t__ table_ptr; struct device dev; } ;
struct fw_rsc_vdev {TYPE_1__* vring; } ;
struct TYPE_2__ {int notifyid; int /*<<< orphan*/  da; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int idr_alloc (int /*<<< orphan*/ *,struct rproc_vring*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rproc_add_carveout (struct rproc*,struct rproc_mem_entry*) ; 
 int /*<<< orphan*/  rproc_alloc_carveout ; 
 scalar_t__ rproc_check_carveout_da (struct rproc*,struct rproc_mem_entry*,int /*<<< orphan*/ ,int) ; 
 struct rproc_mem_entry* rproc_find_carveout_by_name (struct rproc*,char*,int /*<<< orphan*/ ,int) ; 
 struct rproc_mem_entry* rproc_mem_entry_init (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rproc_release_carveout ; 
 int /*<<< orphan*/  vring_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rproc_alloc_vring(struct rproc_vdev *rvdev, int i)
{
	struct rproc *rproc = rvdev->rproc;
	struct device *dev = &rproc->dev;
	struct rproc_vring *rvring = &rvdev->vring[i];
	struct fw_rsc_vdev *rsc;
	int ret, size, notifyid;
	struct rproc_mem_entry *mem;

	/* actual size of vring (in bytes) */
	size = PAGE_ALIGN(vring_size(rvring->len, rvring->align));

	rsc = (void *)rproc->table_ptr + rvdev->rsc_offset;

	/* Search for pre-registered carveout */
	mem = rproc_find_carveout_by_name(rproc, "vdev%dvring%d", rvdev->index,
					  i);
	if (mem) {
		if (rproc_check_carveout_da(rproc, mem, rsc->vring[i].da, size))
			return -ENOMEM;
	} else {
		/* Register carveout in in list */
		mem = rproc_mem_entry_init(dev, 0, 0, size, rsc->vring[i].da,
					   rproc_alloc_carveout,
					   rproc_release_carveout,
					   "vdev%dvring%d",
					   rvdev->index, i);
		if (!mem) {
			dev_err(dev, "Can't allocate memory entry structure\n");
			return -ENOMEM;
		}

		rproc_add_carveout(rproc, mem);
	}

	/*
	 * Assign an rproc-wide unique index for this vring
	 * TODO: assign a notifyid for rvdev updates as well
	 * TODO: support predefined notifyids (via resource table)
	 */
	ret = idr_alloc(&rproc->notifyids, rvring, 0, 0, GFP_KERNEL);
	if (ret < 0) {
		dev_err(dev, "idr_alloc failed: %d\n", ret);
		return ret;
	}
	notifyid = ret;

	/* Potentially bump max_notifyid */
	if (notifyid > rproc->max_notifyid)
		rproc->max_notifyid = notifyid;

	rvring->notifyid = notifyid;

	/* Let the rproc know the notifyid of this vring.*/
	rsc->vring[i].notifyid = notifyid;
	return 0;
}