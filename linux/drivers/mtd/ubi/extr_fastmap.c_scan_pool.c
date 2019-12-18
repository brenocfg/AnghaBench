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
struct ubi_vid_io_buf {int dummy; } ;
struct ubi_vid_hdr {int /*<<< orphan*/  copy_flag; int /*<<< orphan*/  sqnum; int /*<<< orphan*/  lnum; } ;
struct ubi_ec_hdr {int /*<<< orphan*/  ec; int /*<<< orphan*/  image_seq; } ;
struct ubi_device {int image_seq; int /*<<< orphan*/  ec_hdr_alsize; } ;
struct ubi_attach_info {int dummy; } ;
struct ubi_ainf_peb {unsigned long long sqnum; int scrub; int /*<<< orphan*/  copy_flag; void* lnum; } ;
struct list_head {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int UBI_BAD_FASTMAP ; 
 int UBI_IO_BITFLIPS ; 
 int UBI_IO_FF ; 
 int UBI_IO_FF_BITFLIPS ; 
 int /*<<< orphan*/  add_aeb (struct ubi_attach_info*,struct list_head*,int,unsigned long long,int) ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 void* be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_bld (char*,int) ; 
 int /*<<< orphan*/  kfree (struct ubi_ec_hdr*) ; 
 struct ubi_ec_hdr* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int process_pool_aeb (struct ubi_device*,struct ubi_attach_info*,struct ubi_vid_hdr*,struct ubi_ainf_peb*) ; 
 struct ubi_ainf_peb* ubi_alloc_aeb (struct ubi_attach_info*,int,void*) ; 
 struct ubi_vid_io_buf* ubi_alloc_vid_buf (struct ubi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubi_err (struct ubi_device*,char*,...) ; 
 int /*<<< orphan*/  ubi_free_vid_buf (struct ubi_vid_io_buf*) ; 
 struct ubi_vid_hdr* ubi_get_vid_hdr (struct ubi_vid_io_buf*) ; 
 scalar_t__ ubi_io_is_bad (struct ubi_device*,int) ; 
 int ubi_io_read_ec_hdr (struct ubi_device*,int,struct ubi_ec_hdr*,int /*<<< orphan*/ ) ; 
 int ubi_io_read_vid_hdr (struct ubi_device*,int,struct ubi_vid_io_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmap_peb (struct ubi_attach_info*,int) ; 

__attribute__((used)) static int scan_pool(struct ubi_device *ubi, struct ubi_attach_info *ai,
		     __be32 *pebs, int pool_size, unsigned long long *max_sqnum,
		     struct list_head *free)
{
	struct ubi_vid_io_buf *vb;
	struct ubi_vid_hdr *vh;
	struct ubi_ec_hdr *ech;
	struct ubi_ainf_peb *new_aeb;
	int i, pnum, err, ret = 0;

	ech = kzalloc(ubi->ec_hdr_alsize, GFP_KERNEL);
	if (!ech)
		return -ENOMEM;

	vb = ubi_alloc_vid_buf(ubi, GFP_KERNEL);
	if (!vb) {
		kfree(ech);
		return -ENOMEM;
	}

	vh = ubi_get_vid_hdr(vb);

	dbg_bld("scanning fastmap pool: size = %i", pool_size);

	/*
	 * Now scan all PEBs in the pool to find changes which have been made
	 * after the creation of the fastmap
	 */
	for (i = 0; i < pool_size; i++) {
		int scrub = 0;
		int image_seq;

		pnum = be32_to_cpu(pebs[i]);

		if (ubi_io_is_bad(ubi, pnum)) {
			ubi_err(ubi, "bad PEB in fastmap pool!");
			ret = UBI_BAD_FASTMAP;
			goto out;
		}

		err = ubi_io_read_ec_hdr(ubi, pnum, ech, 0);
		if (err && err != UBI_IO_BITFLIPS) {
			ubi_err(ubi, "unable to read EC header! PEB:%i err:%i",
				pnum, err);
			ret = err > 0 ? UBI_BAD_FASTMAP : err;
			goto out;
		} else if (err == UBI_IO_BITFLIPS)
			scrub = 1;

		/*
		 * Older UBI implementations have image_seq set to zero, so
		 * we shouldn't fail if image_seq == 0.
		 */
		image_seq = be32_to_cpu(ech->image_seq);

		if (image_seq && (image_seq != ubi->image_seq)) {
			ubi_err(ubi, "bad image seq: 0x%x, expected: 0x%x",
				be32_to_cpu(ech->image_seq), ubi->image_seq);
			ret = UBI_BAD_FASTMAP;
			goto out;
		}

		err = ubi_io_read_vid_hdr(ubi, pnum, vb, 0);
		if (err == UBI_IO_FF || err == UBI_IO_FF_BITFLIPS) {
			unsigned long long ec = be64_to_cpu(ech->ec);
			unmap_peb(ai, pnum);
			dbg_bld("Adding PEB to free: %i", pnum);

			if (err == UBI_IO_FF_BITFLIPS)
				scrub = 1;

			add_aeb(ai, free, pnum, ec, scrub);
			continue;
		} else if (err == 0 || err == UBI_IO_BITFLIPS) {
			dbg_bld("Found non empty PEB:%i in pool", pnum);

			if (err == UBI_IO_BITFLIPS)
				scrub = 1;

			new_aeb = ubi_alloc_aeb(ai, pnum, be64_to_cpu(ech->ec));
			if (!new_aeb) {
				ret = -ENOMEM;
				goto out;
			}

			new_aeb->lnum = be32_to_cpu(vh->lnum);
			new_aeb->sqnum = be64_to_cpu(vh->sqnum);
			new_aeb->copy_flag = vh->copy_flag;
			new_aeb->scrub = scrub;

			if (*max_sqnum < new_aeb->sqnum)
				*max_sqnum = new_aeb->sqnum;

			err = process_pool_aeb(ubi, ai, vh, new_aeb);
			if (err) {
				ret = err > 0 ? UBI_BAD_FASTMAP : err;
				goto out;
			}
		} else {
			/* We are paranoid and fall back to scanning mode */
			ubi_err(ubi, "fastmap pool PEBs contains damaged PEBs!");
			ret = err > 0 ? UBI_BAD_FASTMAP : err;
			goto out;
		}

	}

out:
	ubi_free_vid_buf(vb);
	kfree(ech);
	return ret;
}