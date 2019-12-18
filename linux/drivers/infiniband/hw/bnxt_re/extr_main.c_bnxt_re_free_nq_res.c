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
typedef  int /*<<< orphan*/  u8 ;
struct bnxt_re_dev {int num_msix; TYPE_1__* nq; int /*<<< orphan*/  chip_ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/ * res; int /*<<< orphan*/  ring_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnxt_qplib_free_nq (TYPE_1__*) ; 
 int /*<<< orphan*/  bnxt_qplib_get_ring_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnxt_re_net_ring_free (struct bnxt_re_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnxt_re_free_nq_res(struct bnxt_re_dev *rdev)
{
	u8 type;
	int i;

	for (i = 0; i < rdev->num_msix - 1; i++) {
		type = bnxt_qplib_get_ring_type(&rdev->chip_ctx);
		bnxt_re_net_ring_free(rdev, rdev->nq[i].ring_id, type);
		rdev->nq[i].res = NULL;
		bnxt_qplib_free_nq(&rdev->nq[i]);
	}
}