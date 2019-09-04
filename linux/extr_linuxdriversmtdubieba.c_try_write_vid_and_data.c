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
struct ubi_volume {int vol_id; TYPE_2__* eba_tbl; struct ubi_device* ubi; } ;
struct ubi_vid_io_buf {int dummy; } ;
struct ubi_device {int /*<<< orphan*/  fm_eba_sem; } ;
struct TYPE_4__ {TYPE_1__* entries; } ;
struct TYPE_3__ {int pnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_eba (char*,int,int,int,int,int) ; 
 int ubi_io_write_data (struct ubi_device*,void const*,int,int,int) ; 
 int ubi_io_write_vid_hdr (struct ubi_device*,int,struct ubi_vid_io_buf*) ; 
 int /*<<< orphan*/  ubi_warn (struct ubi_device*,char*,int,int,int,...) ; 
 int ubi_wl_get_peb (struct ubi_device*) ; 
 int ubi_wl_put_peb (struct ubi_device*,int,int,int,int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int try_write_vid_and_data(struct ubi_volume *vol, int lnum,
				  struct ubi_vid_io_buf *vidb, const void *buf,
				  int offset, int len)
{
	struct ubi_device *ubi = vol->ubi;
	int pnum, opnum, err, vol_id = vol->vol_id;

	pnum = ubi_wl_get_peb(ubi);
	if (pnum < 0) {
		err = pnum;
		goto out_put;
	}

	opnum = vol->eba_tbl->entries[lnum].pnum;

	dbg_eba("write VID hdr and %d bytes at offset %d of LEB %d:%d, PEB %d",
		len, offset, vol_id, lnum, pnum);

	err = ubi_io_write_vid_hdr(ubi, pnum, vidb);
	if (err) {
		ubi_warn(ubi, "failed to write VID header to LEB %d:%d, PEB %d",
			 vol_id, lnum, pnum);
		goto out_put;
	}

	if (len) {
		err = ubi_io_write_data(ubi, buf, pnum, offset, len);
		if (err) {
			ubi_warn(ubi,
				 "failed to write %d bytes at offset %d of LEB %d:%d, PEB %d",
				 len, offset, vol_id, lnum, pnum);
			goto out_put;
		}
	}

	vol->eba_tbl->entries[lnum].pnum = pnum;

out_put:
	up_read(&ubi->fm_eba_sem);

	if (err && pnum >= 0)
		err = ubi_wl_put_peb(ubi, vol_id, lnum, pnum, 1);
	else if (!err && opnum >= 0)
		err = ubi_wl_put_peb(ubi, vol_id, lnum, opnum, 0);

	return err;
}