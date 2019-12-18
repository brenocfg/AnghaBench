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
struct ubi_vid_io_buf {int dummy; } ;
struct ubi_vid_hdr {int /*<<< orphan*/  sqnum; void* lnum; void* data_pad; void* used_ebs; void* data_size; int /*<<< orphan*/  compat; void* vol_id; int /*<<< orphan*/  vol_type; } ;
struct ubi_device {int /*<<< orphan*/  vtbl_size; } ;
struct ubi_attach_info {int /*<<< orphan*/  erase; int /*<<< orphan*/  max_sqnum; } ;
struct TYPE_2__ {int /*<<< orphan*/  list; } ;
struct ubi_ainf_peb {TYPE_1__ u; int /*<<< orphan*/  ec; int /*<<< orphan*/  pnum; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct ubi_ainf_peb*) ; 
 int PTR_ERR (struct ubi_ainf_peb*) ; 
 int /*<<< orphan*/  UBI_LAYOUT_VOLUME_COMPAT ; 
 int UBI_LAYOUT_VOLUME_ID ; 
 int /*<<< orphan*/  UBI_LAYOUT_VOLUME_TYPE ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_gen (char*,int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ubi_add_to_av (struct ubi_device*,struct ubi_attach_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ubi_vid_hdr*,int /*<<< orphan*/ ) ; 
 struct ubi_vid_io_buf* ubi_alloc_vid_buf (struct ubi_device*,int /*<<< orphan*/ ) ; 
 struct ubi_ainf_peb* ubi_early_get_peb (struct ubi_device*,struct ubi_attach_info*) ; 
 int /*<<< orphan*/  ubi_free_aeb (struct ubi_attach_info*,struct ubi_ainf_peb*) ; 
 int /*<<< orphan*/  ubi_free_vid_buf (struct ubi_vid_io_buf*) ; 
 struct ubi_vid_hdr* ubi_get_vid_hdr (struct ubi_vid_io_buf*) ; 
 int ubi_io_write_data (struct ubi_device*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ubi_io_write_vid_hdr (struct ubi_device*,int /*<<< orphan*/ ,struct ubi_vid_io_buf*) ; 

__attribute__((used)) static int create_vtbl(struct ubi_device *ubi, struct ubi_attach_info *ai,
		       int copy, void *vtbl)
{
	int err, tries = 0;
	struct ubi_vid_io_buf *vidb;
	struct ubi_vid_hdr *vid_hdr;
	struct ubi_ainf_peb *new_aeb;

	dbg_gen("create volume table (copy #%d)", copy + 1);

	vidb = ubi_alloc_vid_buf(ubi, GFP_KERNEL);
	if (!vidb)
		return -ENOMEM;

	vid_hdr = ubi_get_vid_hdr(vidb);

retry:
	new_aeb = ubi_early_get_peb(ubi, ai);
	if (IS_ERR(new_aeb)) {
		err = PTR_ERR(new_aeb);
		goto out_free;
	}

	vid_hdr->vol_type = UBI_LAYOUT_VOLUME_TYPE;
	vid_hdr->vol_id = cpu_to_be32(UBI_LAYOUT_VOLUME_ID);
	vid_hdr->compat = UBI_LAYOUT_VOLUME_COMPAT;
	vid_hdr->data_size = vid_hdr->used_ebs =
			     vid_hdr->data_pad = cpu_to_be32(0);
	vid_hdr->lnum = cpu_to_be32(copy);
	vid_hdr->sqnum = cpu_to_be64(++ai->max_sqnum);

	/* The EC header is already there, write the VID header */
	err = ubi_io_write_vid_hdr(ubi, new_aeb->pnum, vidb);
	if (err)
		goto write_error;

	/* Write the layout volume contents */
	err = ubi_io_write_data(ubi, vtbl, new_aeb->pnum, 0, ubi->vtbl_size);
	if (err)
		goto write_error;

	/*
	 * And add it to the attaching information. Don't delete the old version
	 * of this LEB as it will be deleted and freed in 'ubi_add_to_av()'.
	 */
	err = ubi_add_to_av(ubi, ai, new_aeb->pnum, new_aeb->ec, vid_hdr, 0);
	ubi_free_aeb(ai, new_aeb);
	ubi_free_vid_buf(vidb);
	return err;

write_error:
	if (err == -EIO && ++tries <= 5) {
		/*
		 * Probably this physical eraseblock went bad, try to pick
		 * another one.
		 */
		list_add(&new_aeb->u.list, &ai->erase);
		goto retry;
	}
	ubi_free_aeb(ai, new_aeb);
out_free:
	ubi_free_vid_buf(vidb);
	return err;

}