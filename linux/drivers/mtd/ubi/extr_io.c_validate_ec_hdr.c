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
struct ubi_ec_hdr {scalar_t__ version; int /*<<< orphan*/  data_offset; int /*<<< orphan*/  vid_hdr_offset; int /*<<< orphan*/  ec; } ;
struct ubi_device {int vid_hdr_offset; int leb_start; } ;

/* Variables and functions */
 long long UBI_MAX_ERASECOUNTER ; 
 scalar_t__ UBI_VERSION ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 long long be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  ubi_dump_ec_hdr (struct ubi_ec_hdr const*) ; 
 int /*<<< orphan*/  ubi_err (struct ubi_device const*,char*,...) ; 

__attribute__((used)) static int validate_ec_hdr(const struct ubi_device *ubi,
			   const struct ubi_ec_hdr *ec_hdr)
{
	long long ec;
	int vid_hdr_offset, leb_start;

	ec = be64_to_cpu(ec_hdr->ec);
	vid_hdr_offset = be32_to_cpu(ec_hdr->vid_hdr_offset);
	leb_start = be32_to_cpu(ec_hdr->data_offset);

	if (ec_hdr->version != UBI_VERSION) {
		ubi_err(ubi, "node with incompatible UBI version found: this UBI version is %d, image version is %d",
			UBI_VERSION, (int)ec_hdr->version);
		goto bad;
	}

	if (vid_hdr_offset != ubi->vid_hdr_offset) {
		ubi_err(ubi, "bad VID header offset %d, expected %d",
			vid_hdr_offset, ubi->vid_hdr_offset);
		goto bad;
	}

	if (leb_start != ubi->leb_start) {
		ubi_err(ubi, "bad data offset %d, expected %d",
			leb_start, ubi->leb_start);
		goto bad;
	}

	if (ec < 0 || ec > UBI_MAX_ERASECOUNTER) {
		ubi_err(ubi, "bad erase counter %lld", ec);
		goto bad;
	}

	return 0;

bad:
	ubi_err(ubi, "bad EC header");
	ubi_dump_ec_hdr(ec_hdr);
	dump_stack();
	return 1;
}