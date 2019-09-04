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
struct ubi_volume {int changing_leb; scalar_t__ upd_bytes; int /*<<< orphan*/  upd_buf; int /*<<< orphan*/  ch_lnum; scalar_t__ upd_received; int /*<<< orphan*/  vol_id; int /*<<< orphan*/  updating; } ;
struct ubi_leb_change_req {scalar_t__ bytes; int /*<<< orphan*/  lnum; } ;
struct ubi_device {int /*<<< orphan*/  min_io_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dbg_gen (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ubi_assert (int) ; 
 int ubi_eba_atomic_leb_change (struct ubi_device*,struct ubi_volume*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmalloc (int /*<<< orphan*/ ) ; 

int ubi_start_leb_change(struct ubi_device *ubi, struct ubi_volume *vol,
			 const struct ubi_leb_change_req *req)
{
	ubi_assert(!vol->updating && !vol->changing_leb);

	dbg_gen("start changing LEB %d:%d, %u bytes",
		vol->vol_id, req->lnum, req->bytes);
	if (req->bytes == 0)
		return ubi_eba_atomic_leb_change(ubi, vol, req->lnum, NULL, 0);

	vol->upd_bytes = req->bytes;
	vol->upd_received = 0;
	vol->changing_leb = 1;
	vol->ch_lnum = req->lnum;

	vol->upd_buf = vmalloc(ALIGN((int)req->bytes, ubi->min_io_size));
	if (!vol->upd_buf)
		return -ENOMEM;

	return 0;
}