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
typedef  unsigned long u64 ;
struct nd_region {scalar_t__ ndr_start; int /*<<< orphan*/  bb; } ;
struct nd_pfn_sb {int /*<<< orphan*/  dataoff; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct nd_pfn {scalar_t__ mode; TYPE_2__ dev; struct nd_pfn_sb* pfn_sb; struct nd_namespace_common* ndns; } ;
struct TYPE_4__ {scalar_t__ start; } ;
struct nd_namespace_io {TYPE_1__ res; } ;
struct nd_namespace_common {int /*<<< orphan*/  dev; } ;
typedef  int sector_t ;

/* Variables and functions */
 unsigned long ALIGN (int,int /*<<< orphan*/ ) ; 
 unsigned long ALIGN_DOWN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ PFN_MODE_PMEM ; 
 int SZ_4K ; 
 int /*<<< orphan*/  ZERO_PAGE (int /*<<< orphan*/ ) ; 
 int badblocks_check (int /*<<< orphan*/ *,int,int,int*,int*) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*,int,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int,int) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned long min (unsigned long,int /*<<< orphan*/ ) ; 
 int nvdimm_write_bytes (struct nd_namespace_common*,unsigned long,void*,unsigned long,int /*<<< orphan*/ ) ; 
 void* page_address (int /*<<< orphan*/ ) ; 
 struct nd_namespace_io* to_nd_namespace_io (int /*<<< orphan*/ *) ; 
 struct nd_region* to_nd_region (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nd_pfn_clear_memmap_errors(struct nd_pfn *nd_pfn)
{
	struct nd_region *nd_region = to_nd_region(nd_pfn->dev.parent);
	struct nd_namespace_common *ndns = nd_pfn->ndns;
	void *zero_page = page_address(ZERO_PAGE(0));
	struct nd_pfn_sb *pfn_sb = nd_pfn->pfn_sb;
	int num_bad, meta_num, rc, bb_present;
	sector_t first_bad, meta_start;
	struct nd_namespace_io *nsio;

	if (nd_pfn->mode != PFN_MODE_PMEM)
		return 0;

	nsio = to_nd_namespace_io(&ndns->dev);
	meta_start = (SZ_4K + sizeof(*pfn_sb)) >> 9;
	meta_num = (le64_to_cpu(pfn_sb->dataoff) >> 9) - meta_start;

	do {
		unsigned long zero_len;
		u64 nsoff;

		bb_present = badblocks_check(&nd_region->bb, meta_start,
				meta_num, &first_bad, &num_bad);
		if (bb_present) {
			dev_dbg(&nd_pfn->dev, "meta: %x badblocks at %llx\n",
					num_bad, first_bad);
			nsoff = ALIGN_DOWN((nd_region->ndr_start
					+ (first_bad << 9)) - nsio->res.start,
					PAGE_SIZE);
			zero_len = ALIGN(num_bad << 9, PAGE_SIZE);
			while (zero_len) {
				unsigned long chunk = min(zero_len, PAGE_SIZE);

				rc = nvdimm_write_bytes(ndns, nsoff, zero_page,
							chunk, 0);
				if (rc)
					break;

				zero_len -= chunk;
				nsoff += chunk;
			}
			if (rc) {
				dev_err(&nd_pfn->dev,
					"error clearing %x badblocks at %llx\n",
					num_bad, first_bad);
				return rc;
			}
		}
	} while (bb_present);

	return 0;
}