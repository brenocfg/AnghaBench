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
struct ubi_ec_hdr {int /*<<< orphan*/  hdr_crc; } ;
struct ubi_device {int /*<<< orphan*/  ec_hdr_alsize; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  UBI_CRC32_INIT ; 
 int /*<<< orphan*/  UBI_EC_HDR_SIZE ; 
 int /*<<< orphan*/  UBI_EC_HDR_SIZE_CRC ; 
 int UBI_IO_BITFLIPS ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ crc32 (int /*<<< orphan*/ ,struct ubi_ec_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  kfree (struct ubi_ec_hdr*) ; 
 struct ubi_ec_hdr* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtd_is_eccerr (int) ; 
 int self_check_ec_hdr (struct ubi_device const*,int,struct ubi_ec_hdr*) ; 
 int /*<<< orphan*/  ubi_dbg_chk_io (struct ubi_device const*) ; 
 int /*<<< orphan*/  ubi_dump_ec_hdr (struct ubi_ec_hdr*) ; 
 int /*<<< orphan*/  ubi_err (struct ubi_device const*,char*,int,...) ; 
 int ubi_io_read (struct ubi_device const*,struct ubi_ec_hdr*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int self_check_peb_ec_hdr(const struct ubi_device *ubi, int pnum)
{
	int err;
	uint32_t crc, hdr_crc;
	struct ubi_ec_hdr *ec_hdr;

	if (!ubi_dbg_chk_io(ubi))
		return 0;

	ec_hdr = kzalloc(ubi->ec_hdr_alsize, GFP_NOFS);
	if (!ec_hdr)
		return -ENOMEM;

	err = ubi_io_read(ubi, ec_hdr, pnum, 0, UBI_EC_HDR_SIZE);
	if (err && err != UBI_IO_BITFLIPS && !mtd_is_eccerr(err))
		goto exit;

	crc = crc32(UBI_CRC32_INIT, ec_hdr, UBI_EC_HDR_SIZE_CRC);
	hdr_crc = be32_to_cpu(ec_hdr->hdr_crc);
	if (hdr_crc != crc) {
		ubi_err(ubi, "bad CRC, calculated %#08x, read %#08x",
			crc, hdr_crc);
		ubi_err(ubi, "self-check failed for PEB %d", pnum);
		ubi_dump_ec_hdr(ec_hdr);
		dump_stack();
		err = -EINVAL;
		goto exit;
	}

	err = self_check_ec_hdr(ubi, pnum, ec_hdr);

exit:
	kfree(ec_hdr);
	return err;
}