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
typedef  int uint32_t ;
struct ubi_volume {int vol_id; int data_pad; TYPE_2__* eba_tbl; } ;
struct ubi_vid_io_buf {int dummy; } ;
struct ubi_vid_hdr {void* sqnum; void* data_crc; void* used_ebs; void* data_size; int /*<<< orphan*/  vol_type; void* data_pad; int /*<<< orphan*/  compat; void* lnum; void* vol_id; } ;
struct ubi_device {int /*<<< orphan*/  bad_allowed; int /*<<< orphan*/  min_io_size; scalar_t__ ro_mode; } ;
struct TYPE_4__ {TYPE_1__* entries; } ;
struct TYPE_3__ {scalar_t__ pnum; } ;

/* Variables and functions */
 int ALIGN (int,int /*<<< orphan*/ ) ; 
 int EIO ; 
 int ENOMEM ; 
 int EROFS ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  UBI_CRC32_INIT ; 
 int UBI_IO_RETRIES ; 
 int /*<<< orphan*/  UBI_VID_STATIC ; 
 void* cpu_to_be32 (int) ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int crc32 (int /*<<< orphan*/ ,void const*,int) ; 
 int leb_write_lock (struct ubi_device*,int,int) ; 
 int /*<<< orphan*/  leb_write_unlock (struct ubi_device*,int,int) ; 
 int try_write_vid_and_data (struct ubi_volume*,int,struct ubi_vid_io_buf*,void const*,int /*<<< orphan*/ ,int) ; 
 struct ubi_vid_io_buf* ubi_alloc_vid_buf (struct ubi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubi_assert (int) ; 
 int /*<<< orphan*/  ubi_free_vid_buf (struct ubi_vid_io_buf*) ; 
 int /*<<< orphan*/  ubi_get_compat (struct ubi_device*,int) ; 
 struct ubi_vid_hdr* ubi_get_vid_hdr (struct ubi_vid_io_buf*) ; 
 int /*<<< orphan*/  ubi_msg (struct ubi_device*,char*) ; 
 int /*<<< orphan*/  ubi_next_sqnum (struct ubi_device*) ; 
 int /*<<< orphan*/  ubi_ro_mode (struct ubi_device*) ; 

int ubi_eba_write_leb_st(struct ubi_device *ubi, struct ubi_volume *vol,
			 int lnum, const void *buf, int len, int used_ebs)
{
	int err, tries, data_size = len, vol_id = vol->vol_id;
	struct ubi_vid_io_buf *vidb;
	struct ubi_vid_hdr *vid_hdr;
	uint32_t crc;

	if (ubi->ro_mode)
		return -EROFS;

	if (lnum == used_ebs - 1)
		/* If this is the last LEB @len may be unaligned */
		len = ALIGN(data_size, ubi->min_io_size);
	else
		ubi_assert(!(len & (ubi->min_io_size - 1)));

	vidb = ubi_alloc_vid_buf(ubi, GFP_NOFS);
	if (!vidb)
		return -ENOMEM;

	vid_hdr = ubi_get_vid_hdr(vidb);

	err = leb_write_lock(ubi, vol_id, lnum);
	if (err)
		goto out;

	vid_hdr->sqnum = cpu_to_be64(ubi_next_sqnum(ubi));
	vid_hdr->vol_id = cpu_to_be32(vol_id);
	vid_hdr->lnum = cpu_to_be32(lnum);
	vid_hdr->compat = ubi_get_compat(ubi, vol_id);
	vid_hdr->data_pad = cpu_to_be32(vol->data_pad);

	crc = crc32(UBI_CRC32_INIT, buf, data_size);
	vid_hdr->vol_type = UBI_VID_STATIC;
	vid_hdr->data_size = cpu_to_be32(data_size);
	vid_hdr->used_ebs = cpu_to_be32(used_ebs);
	vid_hdr->data_crc = cpu_to_be32(crc);

	ubi_assert(vol->eba_tbl->entries[lnum].pnum < 0);

	for (tries = 0; tries <= UBI_IO_RETRIES; tries++) {
		err = try_write_vid_and_data(vol, lnum, vidb, buf, 0, len);
		if (err != -EIO || !ubi->bad_allowed)
			break;

		vid_hdr->sqnum = cpu_to_be64(ubi_next_sqnum(ubi));
		ubi_msg(ubi, "try another PEB");
	}

	if (err)
		ubi_ro_mode(ubi);

	leb_write_unlock(ubi, vol_id, lnum);

out:
	ubi_free_vid_buf(vidb);

	return err;
}