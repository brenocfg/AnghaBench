#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ubi_volume {int vol_id; int data_pad; TYPE_2__* eba_tbl; } ;
struct ubi_vid_io_buf {int dummy; } ;
struct ubi_vid_hdr {void* sqnum; void* data_pad; int /*<<< orphan*/  compat; void* lnum; void* vol_id; int /*<<< orphan*/  vol_type; } ;
struct ubi_device {scalar_t__ bad_allowed; scalar_t__ ro_mode; } ;
struct TYPE_4__ {TYPE_1__* entries; } ;
struct TYPE_3__ {int pnum; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int EROFS ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int UBI_IO_RETRIES ; 
 int /*<<< orphan*/  UBI_VID_DYNAMIC ; 
 int check_mapping (struct ubi_device*,struct ubi_volume*,int,int*) ; 
 void* cpu_to_be32 (int) ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_eba (char*,int,int,int,int,int) ; 
 int leb_write_lock (struct ubi_device*,int,int) ; 
 int /*<<< orphan*/  leb_write_unlock (struct ubi_device*,int,int) ; 
 int recover_peb (struct ubi_device*,int,int,int,void const*,int,int) ; 
 int try_write_vid_and_data (struct ubi_volume*,int,struct ubi_vid_io_buf*,void const*,int,int) ; 
 struct ubi_vid_io_buf* ubi_alloc_vid_buf (struct ubi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubi_free_vid_buf (struct ubi_vid_io_buf*) ; 
 int /*<<< orphan*/  ubi_get_compat (struct ubi_device*,int) ; 
 struct ubi_vid_hdr* ubi_get_vid_hdr (struct ubi_vid_io_buf*) ; 
 int ubi_io_write_data (struct ubi_device*,void const*,int,int,int) ; 
 int /*<<< orphan*/  ubi_msg (struct ubi_device*,char*) ; 
 int /*<<< orphan*/  ubi_next_sqnum (struct ubi_device*) ; 
 int /*<<< orphan*/  ubi_ro_mode (struct ubi_device*) ; 
 int /*<<< orphan*/  ubi_warn (struct ubi_device*,char*,int) ; 

int ubi_eba_write_leb(struct ubi_device *ubi, struct ubi_volume *vol, int lnum,
		      const void *buf, int offset, int len)
{
	int err, pnum, tries, vol_id = vol->vol_id;
	struct ubi_vid_io_buf *vidb;
	struct ubi_vid_hdr *vid_hdr;

	if (ubi->ro_mode)
		return -EROFS;

	err = leb_write_lock(ubi, vol_id, lnum);
	if (err)
		return err;

	pnum = vol->eba_tbl->entries[lnum].pnum;
	if (pnum >= 0) {
		err = check_mapping(ubi, vol, lnum, &pnum);
		if (err < 0)
			goto out;
	}

	if (pnum >= 0) {
		dbg_eba("write %d bytes at offset %d of LEB %d:%d, PEB %d",
			len, offset, vol_id, lnum, pnum);

		err = ubi_io_write_data(ubi, buf, pnum, offset, len);
		if (err) {
			ubi_warn(ubi, "failed to write data to PEB %d", pnum);
			if (err == -EIO && ubi->bad_allowed)
				err = recover_peb(ubi, pnum, vol_id, lnum, buf,
						  offset, len);
		}

		goto out;
	}

	/*
	 * The logical eraseblock is not mapped. We have to get a free physical
	 * eraseblock and write the volume identifier header there first.
	 */
	vidb = ubi_alloc_vid_buf(ubi, GFP_NOFS);
	if (!vidb) {
		leb_write_unlock(ubi, vol_id, lnum);
		return -ENOMEM;
	}

	vid_hdr = ubi_get_vid_hdr(vidb);

	vid_hdr->vol_type = UBI_VID_DYNAMIC;
	vid_hdr->sqnum = cpu_to_be64(ubi_next_sqnum(ubi));
	vid_hdr->vol_id = cpu_to_be32(vol_id);
	vid_hdr->lnum = cpu_to_be32(lnum);
	vid_hdr->compat = ubi_get_compat(ubi, vol_id);
	vid_hdr->data_pad = cpu_to_be32(vol->data_pad);

	for (tries = 0; tries <= UBI_IO_RETRIES; tries++) {
		err = try_write_vid_and_data(vol, lnum, vidb, buf, offset, len);
		if (err != -EIO || !ubi->bad_allowed)
			break;

		/*
		 * Fortunately, this is the first write operation to this
		 * physical eraseblock, so just put it and request a new one.
		 * We assume that if this physical eraseblock went bad, the
		 * erase code will handle that.
		 */
		vid_hdr->sqnum = cpu_to_be64(ubi_next_sqnum(ubi));
		ubi_msg(ubi, "try another PEB");
	}

	ubi_free_vid_buf(vidb);

out:
	if (err)
		ubi_ro_mode(ubi);

	leb_write_unlock(ubi, vol_id, lnum);

	return err;
}