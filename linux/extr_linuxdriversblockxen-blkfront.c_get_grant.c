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
struct grant {int /*<<< orphan*/  gref; } ;
struct blkfront_ring_info {struct blkfront_info* dev_info; } ;
struct blkfront_info {TYPE_1__* xbdev; scalar_t__ feature_persistent; } ;
typedef  int /*<<< orphan*/  grant_ref_t ;
struct TYPE_2__ {int /*<<< orphan*/  otherend_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ENOSPC ; 
 int /*<<< orphan*/  GRANT_INVALID_REF ; 
 struct grant* get_free_grant (struct blkfront_ring_info*) ; 
 int /*<<< orphan*/  gnttab_claim_grant_reference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gnttab_grant_foreign_access_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grant_foreign_access (struct grant*,struct blkfront_info*) ; 

__attribute__((used)) static struct grant *get_grant(grant_ref_t *gref_head,
			       unsigned long gfn,
			       struct blkfront_ring_info *rinfo)
{
	struct grant *gnt_list_entry = get_free_grant(rinfo);
	struct blkfront_info *info = rinfo->dev_info;

	if (gnt_list_entry->gref != GRANT_INVALID_REF)
		return gnt_list_entry;

	/* Assign a gref to this page */
	gnt_list_entry->gref = gnttab_claim_grant_reference(gref_head);
	BUG_ON(gnt_list_entry->gref == -ENOSPC);
	if (info->feature_persistent)
		grant_foreign_access(gnt_list_entry, info);
	else {
		/* Grant access to the GFN passed by the caller */
		gnttab_grant_foreign_access_ref(gnt_list_entry->gref,
						info->xbdev->otherend_id,
						gfn, 0);
	}

	return gnt_list_entry;
}