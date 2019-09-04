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
struct bnxt_re_dev {struct bnxt_en_dev* en_dev; } ;
struct bnxt_en_dev {TYPE_1__* en_ops; } ;
struct TYPE_2__ {int (* bnxt_free_msix ) (struct bnxt_en_dev*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_ROCE_ULP ; 
 int EINVAL ; 
 int stub1 (struct bnxt_en_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnxt_re_free_msix(struct bnxt_re_dev *rdev)
{
	struct bnxt_en_dev *en_dev;
	int rc;

	if (!rdev)
		return -EINVAL;

	en_dev = rdev->en_dev;


	rc = en_dev->en_ops->bnxt_free_msix(rdev->en_dev, BNXT_ROCE_ULP);

	return rc;
}