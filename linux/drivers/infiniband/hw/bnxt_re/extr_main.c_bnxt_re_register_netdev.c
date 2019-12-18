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
struct TYPE_4__ {int /*<<< orphan*/  pdev; } ;
struct bnxt_re_dev {struct bnxt_en_dev* en_dev; TYPE_2__ qplib_res; } ;
struct bnxt_en_dev {int /*<<< orphan*/  pdev; TYPE_1__* en_ops; } ;
struct TYPE_3__ {int (* bnxt_register_device ) (struct bnxt_en_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct bnxt_re_dev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_ROCE_ULP ; 
 int EINVAL ; 
 int /*<<< orphan*/  bnxt_re_ulp_ops ; 
 int stub1 (struct bnxt_en_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct bnxt_re_dev*) ; 

__attribute__((used)) static int bnxt_re_register_netdev(struct bnxt_re_dev *rdev)
{
	struct bnxt_en_dev *en_dev;
	int rc = 0;

	if (!rdev)
		return -EINVAL;

	en_dev = rdev->en_dev;

	rc = en_dev->en_ops->bnxt_register_device(en_dev, BNXT_ROCE_ULP,
						  &bnxt_re_ulp_ops, rdev);
	rdev->qplib_res.pdev = rdev->en_dev->pdev;
	return rc;
}