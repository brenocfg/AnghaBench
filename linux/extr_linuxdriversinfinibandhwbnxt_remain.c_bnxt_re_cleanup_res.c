#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ rcfw; } ;
struct bnxt_re_dev {int num_msix; TYPE_3__ qplib_res; TYPE_2__* nq; } ;
struct TYPE_4__ {scalar_t__ max_elements; } ;
struct TYPE_5__ {TYPE_1__ hwq; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnxt_qplib_cleanup_res (TYPE_3__*) ; 
 int /*<<< orphan*/  bnxt_qplib_disable_nq (TYPE_2__*) ; 

__attribute__((used)) static void bnxt_re_cleanup_res(struct bnxt_re_dev *rdev)
{
	int i;

	if (rdev->nq[0].hwq.max_elements) {
		for (i = 1; i < rdev->num_msix; i++)
			bnxt_qplib_disable_nq(&rdev->nq[i - 1]);
	}

	if (rdev->qplib_res.rcfw)
		bnxt_qplib_cleanup_res(&rdev->qplib_res);
}