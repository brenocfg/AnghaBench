#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bnxt_re_dev {int num_msix; TYPE_2__* msix_entries; int /*<<< orphan*/ * nq; TYPE_1__* en_dev; int /*<<< orphan*/  qplib_res; } ;
struct TYPE_4__ {int /*<<< orphan*/  db_offset; int /*<<< orphan*/  vector; } ;
struct TYPE_3__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int bnxt_qplib_enable_nq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnxt_qplib_init_res (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnxt_re_cqn_handler ; 
 int /*<<< orphan*/  bnxt_re_srqn_handler ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rdev_to_dev (struct bnxt_re_dev*) ; 

__attribute__((used)) static int bnxt_re_init_res(struct bnxt_re_dev *rdev)
{
	int rc = 0, i;

	bnxt_qplib_init_res(&rdev->qplib_res);

	for (i = 1; i < rdev->num_msix ; i++) {
		rc = bnxt_qplib_enable_nq(rdev->en_dev->pdev, &rdev->nq[i - 1],
					  i - 1, rdev->msix_entries[i].vector,
					  rdev->msix_entries[i].db_offset,
					  &bnxt_re_cqn_handler,
					  &bnxt_re_srqn_handler);

		if (rc) {
			dev_err(rdev_to_dev(rdev),
				"Failed to enable NQ with rc = 0x%x", rc);
			goto fail;
		}
	}
	return 0;
fail:
	return rc;
}