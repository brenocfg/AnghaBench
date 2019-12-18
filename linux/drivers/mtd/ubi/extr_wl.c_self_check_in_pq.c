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
struct ubi_wl_entry {int /*<<< orphan*/  ec; int /*<<< orphan*/  pnum; } ;
struct ubi_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dump_stack () ; 
 scalar_t__ in_pq (struct ubi_device const*,struct ubi_wl_entry*) ; 
 int /*<<< orphan*/  ubi_dbg_chk_gen (struct ubi_device const*) ; 
 int /*<<< orphan*/  ubi_err (struct ubi_device const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int self_check_in_pq(const struct ubi_device *ubi,
			    struct ubi_wl_entry *e)
{
	if (!ubi_dbg_chk_gen(ubi))
		return 0;

	if (in_pq(ubi, e))
		return 0;

	ubi_err(ubi, "self-check failed for PEB %d, EC %d, Protect queue",
		e->pnum, e->ec);
	dump_stack();
	return -EINVAL;
}