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
struct ubi_vid_hdr {int /*<<< orphan*/  sqnum; int /*<<< orphan*/  vol_id; } ;
struct ubi_attach_info {int /*<<< orphan*/  fastmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  list; } ;
struct ubi_ainf_peb {int /*<<< orphan*/  sqnum; int /*<<< orphan*/  vol_id; TYPE_1__ u; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_bld (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ubi_ainf_peb* ubi_alloc_aeb (struct ubi_attach_info*,int,int) ; 

__attribute__((used)) static int add_fastmap(struct ubi_attach_info *ai, int pnum,
		       struct ubi_vid_hdr *vid_hdr, int ec)
{
	struct ubi_ainf_peb *aeb;

	aeb = ubi_alloc_aeb(ai, pnum, ec);
	if (!aeb)
		return -ENOMEM;

	aeb->vol_id = be32_to_cpu(vid_hdr->vol_id);
	aeb->sqnum = be64_to_cpu(vid_hdr->sqnum);
	list_add(&aeb->u.list, &ai->fastmap);

	dbg_bld("add to fastmap list: PEB %d, vol_id %d, sqnum: %llu", pnum,
		aeb->vol_id, aeb->sqnum);

	return 0;
}