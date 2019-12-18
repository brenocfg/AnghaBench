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
struct siw_mr {int /*<<< orphan*/  mem; } ;
struct siw_device {int /*<<< orphan*/  num_mr; } ;
struct ib_udata {int dummy; } ;
struct ib_mr {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_rcu (struct siw_mr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  siw_dbg_mem (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  siw_mr_drop_mem (struct siw_mr*) ; 
 struct siw_device* to_siw_dev (int /*<<< orphan*/ ) ; 
 struct siw_mr* to_siw_mr (struct ib_mr*) ; 

int siw_dereg_mr(struct ib_mr *base_mr, struct ib_udata *udata)
{
	struct siw_mr *mr = to_siw_mr(base_mr);
	struct siw_device *sdev = to_siw_dev(base_mr->device);

	siw_dbg_mem(mr->mem, "deregister MR\n");

	atomic_dec(&sdev->num_mr);

	siw_mr_drop_mem(mr);
	kfree_rcu(mr, rcu);

	return 0;
}