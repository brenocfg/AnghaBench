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
struct ubi_ec_hdr {int /*<<< orphan*/  ec; } ;
struct ubi_device {int /*<<< orphan*/  ec_hdr_alsize; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int UBI_IO_BITFLIPS ; 
 long long be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  kfree (struct ubi_ec_hdr*) ; 
 struct ubi_ec_hdr* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubi_dbg_chk_gen (struct ubi_device*) ; 
 int /*<<< orphan*/  ubi_err (struct ubi_device*,char*,long long,...) ; 
 int ubi_io_read_ec_hdr (struct ubi_device*,int,struct ubi_ec_hdr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int self_check_ec(struct ubi_device *ubi, int pnum, int ec)
{
	int err;
	long long read_ec;
	struct ubi_ec_hdr *ec_hdr;

	if (!ubi_dbg_chk_gen(ubi))
		return 0;

	ec_hdr = kzalloc(ubi->ec_hdr_alsize, GFP_NOFS);
	if (!ec_hdr)
		return -ENOMEM;

	err = ubi_io_read_ec_hdr(ubi, pnum, ec_hdr, 0);
	if (err && err != UBI_IO_BITFLIPS) {
		/* The header does not have to exist */
		err = 0;
		goto out_free;
	}

	read_ec = be64_to_cpu(ec_hdr->ec);
	if (ec != read_ec && read_ec - ec > 1) {
		ubi_err(ubi, "self-check failed for PEB %d", pnum);
		ubi_err(ubi, "read EC is %lld, should be %d", read_ec, ec);
		dump_stack();
		err = 1;
	} else
		err = 0;

out_free:
	kfree(ec_hdr);
	return err;
}