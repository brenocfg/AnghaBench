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
struct ubi_ec_hdr {int /*<<< orphan*/  magic; } ;
struct ubi_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ UBI_EC_HDR_MAGIC ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  ubi_dbg_chk_io (struct ubi_device const*) ; 
 int /*<<< orphan*/  ubi_dump_ec_hdr (struct ubi_ec_hdr const*) ; 
 int /*<<< orphan*/  ubi_err (struct ubi_device const*,char*,int,...) ; 
 int validate_ec_hdr (struct ubi_device const*,struct ubi_ec_hdr const*) ; 

__attribute__((used)) static int self_check_ec_hdr(const struct ubi_device *ubi, int pnum,
			     const struct ubi_ec_hdr *ec_hdr)
{
	int err;
	uint32_t magic;

	if (!ubi_dbg_chk_io(ubi))
		return 0;

	magic = be32_to_cpu(ec_hdr->magic);
	if (magic != UBI_EC_HDR_MAGIC) {
		ubi_err(ubi, "bad magic %#08x, must be %#08x",
			magic, UBI_EC_HDR_MAGIC);
		goto fail;
	}

	err = validate_ec_hdr(ubi, ec_hdr);
	if (err) {
		ubi_err(ubi, "self-check failed for PEB %d", pnum);
		goto fail;
	}

	return 0;

fail:
	ubi_dump_ec_hdr(ec_hdr);
	dump_stack();
	return -EINVAL;
}