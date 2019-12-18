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
typedef  scalar_t__ uint32_t ;
struct ubi_vid_io_buf {void* buffer; } ;
struct ubi_vid_hdr {int /*<<< orphan*/  hdr_crc; } ;
struct ubi_device {int /*<<< orphan*/  vid_hdr_alsize; int /*<<< orphan*/  vid_hdr_aloffset; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  UBI_CRC32_INIT ; 
 int UBI_IO_BITFLIPS ; 
 int /*<<< orphan*/  UBI_VID_HDR_SIZE_CRC ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ crc32 (int /*<<< orphan*/ ,struct ubi_vid_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  mtd_is_eccerr (int) ; 
 int self_check_vid_hdr (struct ubi_device const*,int,struct ubi_vid_hdr*) ; 
 struct ubi_vid_io_buf* ubi_alloc_vid_buf (struct ubi_device const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubi_dbg_chk_io (struct ubi_device const*) ; 
 int /*<<< orphan*/  ubi_dump_vid_hdr (struct ubi_vid_hdr*) ; 
 int /*<<< orphan*/  ubi_err (struct ubi_device const*,char*,int,...) ; 
 int /*<<< orphan*/  ubi_free_vid_buf (struct ubi_vid_io_buf*) ; 
 struct ubi_vid_hdr* ubi_get_vid_hdr (struct ubi_vid_io_buf*) ; 
 int ubi_io_read (struct ubi_device const*,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int self_check_peb_vid_hdr(const struct ubi_device *ubi, int pnum)
{
	int err;
	uint32_t crc, hdr_crc;
	struct ubi_vid_io_buf *vidb;
	struct ubi_vid_hdr *vid_hdr;
	void *p;

	if (!ubi_dbg_chk_io(ubi))
		return 0;

	vidb = ubi_alloc_vid_buf(ubi, GFP_NOFS);
	if (!vidb)
		return -ENOMEM;

	vid_hdr = ubi_get_vid_hdr(vidb);
	p = vidb->buffer;
	err = ubi_io_read(ubi, p, pnum, ubi->vid_hdr_aloffset,
			  ubi->vid_hdr_alsize);
	if (err && err != UBI_IO_BITFLIPS && !mtd_is_eccerr(err))
		goto exit;

	crc = crc32(UBI_CRC32_INIT, vid_hdr, UBI_VID_HDR_SIZE_CRC);
	hdr_crc = be32_to_cpu(vid_hdr->hdr_crc);
	if (hdr_crc != crc) {
		ubi_err(ubi, "bad VID header CRC at PEB %d, calculated %#08x, read %#08x",
			pnum, crc, hdr_crc);
		ubi_err(ubi, "self-check failed for PEB %d", pnum);
		ubi_dump_vid_hdr(vid_hdr);
		dump_stack();
		err = -EINVAL;
		goto exit;
	}

	err = self_check_vid_hdr(ubi, pnum, vid_hdr);

exit:
	ubi_free_vid_buf(vidb);
	return err;
}