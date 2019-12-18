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
struct ubi_device {int peb_count; scalar_t__* lookuptbl; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ test_bit (int,unsigned long*) ; 
 int /*<<< orphan*/  ubi_dbg_chk_fastmap (struct ubi_device*) ; 
 int /*<<< orphan*/  ubi_err (struct ubi_device*,char*,int) ; 

__attribute__((used)) static int self_check_seen(struct ubi_device *ubi, unsigned long *seen)
{
	int pnum, ret = 0;

	if (!ubi_dbg_chk_fastmap(ubi) || !seen)
		return 0;

	for (pnum = 0; pnum < ubi->peb_count; pnum++) {
		if (test_bit(pnum, seen) && ubi->lookuptbl[pnum]) {
			ubi_err(ubi, "self-check failed for PEB %d, fastmap didn't see it", pnum);
			ret = -EINVAL;
		}
	}

	return ret;
}