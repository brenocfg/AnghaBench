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
struct ubi_wl_entry {int /*<<< orphan*/  pnum; } ;
struct ubi_vid_io_buf {int dummy; } ;
struct ubi_vid_hdr {int /*<<< orphan*/  sqnum; } ;
struct ubi_fastmap_layout {int used_blocks; struct ubi_wl_entry** e; } ;
struct ubi_device {struct ubi_fastmap_layout* fm; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  UBI_FM_SB_VOLUME_ID ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ubi_fastmap_layout*) ; 
 struct ubi_fastmap_layout* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct ubi_vid_io_buf* new_fm_vbuf (struct ubi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubi_free_vid_buf (struct ubi_vid_io_buf*) ; 
 struct ubi_vid_hdr* ubi_get_vid_hdr (struct ubi_vid_io_buf*) ; 
 int ubi_io_write_vid_hdr (struct ubi_device*,int /*<<< orphan*/ ,struct ubi_vid_io_buf*) ; 
 int /*<<< orphan*/  ubi_next_sqnum (struct ubi_device*) ; 
 struct ubi_wl_entry* ubi_wl_get_fm_peb (struct ubi_device*,int) ; 
 int /*<<< orphan*/  ubi_wl_put_fm_peb (struct ubi_device*,struct ubi_wl_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int invalidate_fastmap(struct ubi_device *ubi)
{
	int ret;
	struct ubi_fastmap_layout *fm;
	struct ubi_wl_entry *e;
	struct ubi_vid_io_buf *vb = NULL;
	struct ubi_vid_hdr *vh;

	if (!ubi->fm)
		return 0;

	ubi->fm = NULL;

	ret = -ENOMEM;
	fm = kzalloc(sizeof(*fm), GFP_KERNEL);
	if (!fm)
		goto out;

	vb = new_fm_vbuf(ubi, UBI_FM_SB_VOLUME_ID);
	if (!vb)
		goto out_free_fm;

	vh = ubi_get_vid_hdr(vb);

	ret = -ENOSPC;
	e = ubi_wl_get_fm_peb(ubi, 1);
	if (!e)
		goto out_free_fm;

	/*
	 * Create fake fastmap such that UBI will fall back
	 * to scanning mode.
	 */
	vh->sqnum = cpu_to_be64(ubi_next_sqnum(ubi));
	ret = ubi_io_write_vid_hdr(ubi, e->pnum, vb);
	if (ret < 0) {
		ubi_wl_put_fm_peb(ubi, e, 0, 0);
		goto out_free_fm;
	}

	fm->used_blocks = 1;
	fm->e[0] = e;

	ubi->fm = fm;

out:
	ubi_free_vid_buf(vb);
	return ret;

out_free_fm:
	kfree(fm);
	goto out;
}