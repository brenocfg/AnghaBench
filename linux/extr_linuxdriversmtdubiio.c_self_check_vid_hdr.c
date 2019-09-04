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
struct ubi_vid_hdr {int /*<<< orphan*/  magic; } ;
struct ubi_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ UBI_VID_HDR_MAGIC ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  ubi_dbg_chk_io (struct ubi_device const*) ; 
 int /*<<< orphan*/  ubi_dump_vid_hdr (struct ubi_vid_hdr const*) ; 
 int /*<<< orphan*/  ubi_err (struct ubi_device const*,char*,int,...) ; 
 int validate_vid_hdr (struct ubi_device const*,struct ubi_vid_hdr const*) ; 

__attribute__((used)) static int self_check_vid_hdr(const struct ubi_device *ubi, int pnum,
			      const struct ubi_vid_hdr *vid_hdr)
{
	int err;
	uint32_t magic;

	if (!ubi_dbg_chk_io(ubi))
		return 0;

	magic = be32_to_cpu(vid_hdr->magic);
	if (magic != UBI_VID_HDR_MAGIC) {
		ubi_err(ubi, "bad VID header magic %#08x at PEB %d, must be %#08x",
			magic, pnum, UBI_VID_HDR_MAGIC);
		goto fail;
	}

	err = validate_vid_hdr(ubi, vid_hdr);
	if (err) {
		ubi_err(ubi, "self-check failed for PEB %d", pnum);
		goto fail;
	}

	return err;

fail:
	ubi_err(ubi, "self-check failed for PEB %d", pnum);
	ubi_dump_vid_hdr(vid_hdr);
	dump_stack();
	return -EINVAL;

}