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
struct bnxt_re_dev {int num_vfs; int /*<<< orphan*/  qplib_ctx; int /*<<< orphan*/  rcfw; int /*<<< orphan*/  qplib_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnxt_qplib_set_func_resources (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnxt_re_set_resource_limits (struct bnxt_re_dev*) ; 

__attribute__((used)) static void bnxt_re_sriov_config(void *p, int num_vfs)
{
	struct bnxt_re_dev *rdev = p;

	if (!rdev)
		return;

	rdev->num_vfs = num_vfs;
	bnxt_re_set_resource_limits(rdev);
	bnxt_qplib_set_func_resources(&rdev->qplib_res, &rdev->rcfw,
				      &rdev->qplib_ctx);
}