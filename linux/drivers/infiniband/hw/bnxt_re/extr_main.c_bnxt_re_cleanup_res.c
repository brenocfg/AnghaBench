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
struct TYPE_2__ {scalar_t__ rcfw; } ;
struct bnxt_re_dev {int num_msix; TYPE_1__ qplib_res; int /*<<< orphan*/ * nq; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnxt_qplib_cleanup_res (TYPE_1__*) ; 
 int /*<<< orphan*/  bnxt_qplib_disable_nq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnxt_re_cleanup_res(struct bnxt_re_dev *rdev)
{
	int i;

	for (i = 1; i < rdev->num_msix; i++)
		bnxt_qplib_disable_nq(&rdev->nq[i - 1]);

	if (rdev->qplib_res.rcfw)
		bnxt_qplib_cleanup_res(&rdev->qplib_res);
}