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
struct ubi_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  ubi_dbg_chk_io (struct ubi_device const*) ; 
 int /*<<< orphan*/  ubi_err (struct ubi_device const*,char*,int) ; 
 int ubi_io_is_bad (struct ubi_device const*,int) ; 

__attribute__((used)) static int self_check_not_bad(const struct ubi_device *ubi, int pnum)
{
	int err;

	if (!ubi_dbg_chk_io(ubi))
		return 0;

	err = ubi_io_is_bad(ubi, pnum);
	if (!err)
		return err;

	ubi_err(ubi, "self-check failed for PEB %d", pnum);
	dump_stack();
	return err > 0 ? -EINVAL : err;
}