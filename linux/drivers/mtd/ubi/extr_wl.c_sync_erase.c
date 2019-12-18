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
struct ubi_wl_entry {unsigned long long ec; int /*<<< orphan*/  pnum; } ;
struct ubi_ec_hdr {int /*<<< orphan*/  ec; } ;
struct ubi_device {unsigned long long max_ec; int /*<<< orphan*/  wl_lock; int /*<<< orphan*/  ec_hdr_alsize; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 unsigned long long UBI_MAX_ERASECOUNTER ; 
 int /*<<< orphan*/  cpu_to_be64 (unsigned long long) ; 
 int /*<<< orphan*/  dbg_wl (char*,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  kfree (struct ubi_ec_hdr*) ; 
 struct ubi_ec_hdr* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int self_check_ec (struct ubi_device*,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubi_err (struct ubi_device*,char*,int /*<<< orphan*/ ,unsigned long long) ; 
 int ubi_io_sync_erase (struct ubi_device*,int /*<<< orphan*/ ,int) ; 
 int ubi_io_write_ec_hdr (struct ubi_device*,int /*<<< orphan*/ ,struct ubi_ec_hdr*) ; 

__attribute__((used)) static int sync_erase(struct ubi_device *ubi, struct ubi_wl_entry *e,
		      int torture)
{
	int err;
	struct ubi_ec_hdr *ec_hdr;
	unsigned long long ec = e->ec;

	dbg_wl("erase PEB %d, old EC %llu", e->pnum, ec);

	err = self_check_ec(ubi, e->pnum, e->ec);
	if (err)
		return -EINVAL;

	ec_hdr = kzalloc(ubi->ec_hdr_alsize, GFP_NOFS);
	if (!ec_hdr)
		return -ENOMEM;

	err = ubi_io_sync_erase(ubi, e->pnum, torture);
	if (err < 0)
		goto out_free;

	ec += err;
	if (ec > UBI_MAX_ERASECOUNTER) {
		/*
		 * Erase counter overflow. Upgrade UBI and use 64-bit
		 * erase counters internally.
		 */
		ubi_err(ubi, "erase counter overflow at PEB %d, EC %llu",
			e->pnum, ec);
		err = -EINVAL;
		goto out_free;
	}

	dbg_wl("erased PEB %d, new EC %llu", e->pnum, ec);

	ec_hdr->ec = cpu_to_be64(ec);

	err = ubi_io_write_ec_hdr(ubi, e->pnum, ec_hdr);
	if (err)
		goto out_free;

	e->ec = ec;
	spin_lock(&ubi->wl_lock);
	if (e->ec > ubi->max_ec)
		ubi->max_ec = e->ec;
	spin_unlock(&ubi->wl_lock);

out_free:
	kfree(ec_hdr);
	return err;
}