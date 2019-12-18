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
struct rproc_mem_entry {int rsc_offset; int /*<<< orphan*/  flags; } ;
struct device {int dummy; } ;
struct rproc {struct device dev; } ;
struct fw_rsc_carveout {int /*<<< orphan*/  flags; int /*<<< orphan*/  name; int /*<<< orphan*/  da; int /*<<< orphan*/  len; int /*<<< orphan*/  pa; scalar_t__ reserved; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int FW_RSC_ADDR_ANY ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  rproc_add_carveout (struct rproc*,struct rproc_mem_entry*) ; 
 int /*<<< orphan*/  rproc_alloc_carveout ; 
 scalar_t__ rproc_check_carveout_da (struct rproc*,struct rproc_mem_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rproc_mem_entry* rproc_find_carveout_by_name (struct rproc*,int /*<<< orphan*/ ) ; 
 struct rproc_mem_entry* rproc_mem_entry_init (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rproc_release_carveout ; 

__attribute__((used)) static int rproc_handle_carveout(struct rproc *rproc,
				 struct fw_rsc_carveout *rsc,
				 int offset, int avail)
{
	struct rproc_mem_entry *carveout;
	struct device *dev = &rproc->dev;

	if (sizeof(*rsc) > avail) {
		dev_err(dev, "carveout rsc is truncated\n");
		return -EINVAL;
	}

	/* make sure reserved bytes are zeroes */
	if (rsc->reserved) {
		dev_err(dev, "carveout rsc has non zero reserved bytes\n");
		return -EINVAL;
	}

	dev_dbg(dev, "carveout rsc: name: %s, da 0x%x, pa 0x%x, len 0x%x, flags 0x%x\n",
		rsc->name, rsc->da, rsc->pa, rsc->len, rsc->flags);

	/*
	 * Check carveout rsc already part of a registered carveout,
	 * Search by name, then check the da and length
	 */
	carveout = rproc_find_carveout_by_name(rproc, rsc->name);

	if (carveout) {
		if (carveout->rsc_offset != FW_RSC_ADDR_ANY) {
			dev_err(dev,
				"Carveout already associated to resource table\n");
			return -ENOMEM;
		}

		if (rproc_check_carveout_da(rproc, carveout, rsc->da, rsc->len))
			return -ENOMEM;

		/* Update memory carveout with resource table info */
		carveout->rsc_offset = offset;
		carveout->flags = rsc->flags;

		return 0;
	}

	/* Register carveout in in list */
	carveout = rproc_mem_entry_init(dev, 0, 0, rsc->len, rsc->da,
					rproc_alloc_carveout,
					rproc_release_carveout, rsc->name);
	if (!carveout) {
		dev_err(dev, "Can't allocate memory entry structure\n");
		return -ENOMEM;
	}

	carveout->flags = rsc->flags;
	carveout->rsc_offset = offset;
	rproc_add_carveout(rproc, carveout);

	return 0;
}