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
typedef  int /*<<< orphan*/  uint32_t ;
struct ubi_ec_hdr {void* hdr_crc; void* image_seq; void* data_offset; void* vid_hdr_offset; int /*<<< orphan*/  version; void* magic; } ;
struct ubi_device {int peb_count; int /*<<< orphan*/  ec_hdr_alsize; int /*<<< orphan*/  image_seq; int /*<<< orphan*/  leb_start; int /*<<< orphan*/  vid_hdr_offset; } ;

/* Variables and functions */
 int EROFS ; 
 int /*<<< orphan*/  POWER_CUT_EC_WRITE ; 
 int /*<<< orphan*/  UBI_CRC32_INIT ; 
 int /*<<< orphan*/  UBI_EC_HDR_MAGIC ; 
 int /*<<< orphan*/  UBI_EC_HDR_SIZE_CRC ; 
 int /*<<< orphan*/  UBI_VERSION ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crc32 (int /*<<< orphan*/ ,struct ubi_ec_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_io (char*,int) ; 
 int self_check_ec_hdr (struct ubi_device*,int,struct ubi_ec_hdr*) ; 
 int /*<<< orphan*/  ubi_assert (int) ; 
 scalar_t__ ubi_dbg_power_cut (struct ubi_device*,int /*<<< orphan*/ ) ; 
 int ubi_io_write (struct ubi_device*,struct ubi_ec_hdr*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ubi_io_write_ec_hdr(struct ubi_device *ubi, int pnum,
			struct ubi_ec_hdr *ec_hdr)
{
	int err;
	uint32_t crc;

	dbg_io("write EC header to PEB %d", pnum);
	ubi_assert(pnum >= 0 &&  pnum < ubi->peb_count);

	ec_hdr->magic = cpu_to_be32(UBI_EC_HDR_MAGIC);
	ec_hdr->version = UBI_VERSION;
	ec_hdr->vid_hdr_offset = cpu_to_be32(ubi->vid_hdr_offset);
	ec_hdr->data_offset = cpu_to_be32(ubi->leb_start);
	ec_hdr->image_seq = cpu_to_be32(ubi->image_seq);
	crc = crc32(UBI_CRC32_INIT, ec_hdr, UBI_EC_HDR_SIZE_CRC);
	ec_hdr->hdr_crc = cpu_to_be32(crc);

	err = self_check_ec_hdr(ubi, pnum, ec_hdr);
	if (err)
		return err;

	if (ubi_dbg_power_cut(ubi, POWER_CUT_EC_WRITE))
		return -EROFS;

	err = ubi_io_write(ubi, ec_hdr, pnum, 0, ubi->ec_hdr_alsize);
	return err;
}