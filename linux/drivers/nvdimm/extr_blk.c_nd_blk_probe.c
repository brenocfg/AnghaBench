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
struct nd_namespace_common {int /*<<< orphan*/  rw_bytes; int /*<<< orphan*/  dev; } ;
struct nd_namespace_blk {int /*<<< orphan*/  size; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ IS_ERR (struct nd_namespace_common*) ; 
 int PTR_ERR (struct nd_namespace_common*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct nd_namespace_blk*) ; 
 scalar_t__ is_nd_btt (struct device*) ; 
 scalar_t__ nd_btt_probe (struct device*,struct nd_namespace_common*) ; 
 int nsblk_attach_disk (struct nd_namespace_blk*) ; 
 int /*<<< orphan*/  nsblk_rw_bytes ; 
 int nvdimm_namespace_attach_btt (struct nd_namespace_common*) ; 
 int /*<<< orphan*/  nvdimm_namespace_capacity (struct nd_namespace_common*) ; 
 struct nd_namespace_common* nvdimm_namespace_common_probe (struct device*) ; 
 struct nd_namespace_blk* to_nd_namespace_blk (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nd_blk_probe(struct device *dev)
{
	struct nd_namespace_common *ndns;
	struct nd_namespace_blk *nsblk;

	ndns = nvdimm_namespace_common_probe(dev);
	if (IS_ERR(ndns))
		return PTR_ERR(ndns);

	nsblk = to_nd_namespace_blk(&ndns->dev);
	nsblk->size = nvdimm_namespace_capacity(ndns);
	dev_set_drvdata(dev, nsblk);

	ndns->rw_bytes = nsblk_rw_bytes;
	if (is_nd_btt(dev))
		return nvdimm_namespace_attach_btt(ndns);
	else if (nd_btt_probe(dev, ndns) == 0) {
		/* we'll come back as btt-blk */
		return -ENXIO;
	} else
		return nsblk_attach_disk(nsblk);
}