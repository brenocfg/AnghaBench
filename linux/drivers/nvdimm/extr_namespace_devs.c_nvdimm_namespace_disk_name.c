#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct nd_region {int id; } ;
struct nd_namespace_pmem {int id; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct nd_namespace_common {TYPE_1__ dev; scalar_t__ claim; } ;
struct nd_namespace_blk {int id; } ;

/* Variables and functions */
 scalar_t__ is_namespace_blk (TYPE_1__*) ; 
 scalar_t__ is_namespace_io (TYPE_1__*) ; 
 scalar_t__ is_namespace_pmem (TYPE_1__*) ; 
 scalar_t__ is_nd_btt (scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 
 struct nd_namespace_blk* to_nd_namespace_blk (TYPE_1__*) ; 
 struct nd_namespace_pmem* to_nd_namespace_pmem (TYPE_1__*) ; 
 struct nd_region* to_nd_region (int /*<<< orphan*/ ) ; 

const char *nvdimm_namespace_disk_name(struct nd_namespace_common *ndns,
		char *name)
{
	struct nd_region *nd_region = to_nd_region(ndns->dev.parent);
	const char *suffix = NULL;

	if (ndns->claim && is_nd_btt(ndns->claim))
		suffix = "s";

	if (is_namespace_pmem(&ndns->dev) || is_namespace_io(&ndns->dev)) {
		int nsidx = 0;

		if (is_namespace_pmem(&ndns->dev)) {
			struct nd_namespace_pmem *nspm;

			nspm = to_nd_namespace_pmem(&ndns->dev);
			nsidx = nspm->id;
		}

		if (nsidx)
			sprintf(name, "pmem%d.%d%s", nd_region->id, nsidx,
					suffix ? suffix : "");
		else
			sprintf(name, "pmem%d%s", nd_region->id,
					suffix ? suffix : "");
	} else if (is_namespace_blk(&ndns->dev)) {
		struct nd_namespace_blk *nsblk;

		nsblk = to_nd_namespace_blk(&ndns->dev);
		sprintf(name, "ndblk%d.%d%s", nd_region->id, nsblk->id,
				suffix ? suffix : "");
	} else {
		return NULL;
	}

	return name;
}