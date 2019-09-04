#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ state; } ;
struct res_qp {TYPE_1__ com; int /*<<< orphan*/  ref_count; int /*<<< orphan*/  mcg_list; } ;

/* Variables and functions */
 int EBUSY ; 
 int EPERM ; 
 scalar_t__ RES_QP_BUSY ; 
 scalar_t__ RES_QP_RESERVED ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int remove_qp_ok(struct res_qp *res)
{
	if (res->com.state == RES_QP_BUSY || atomic_read(&res->ref_count) ||
	    !list_empty(&res->mcg_list)) {
		pr_err("resource tracker: fail to remove qp, state %d, ref_count %d\n",
		       res->com.state, atomic_read(&res->ref_count));
		return -EBUSY;
	} else if (res->com.state != RES_QP_RESERVED) {
		return -EPERM;
	}

	return 0;
}