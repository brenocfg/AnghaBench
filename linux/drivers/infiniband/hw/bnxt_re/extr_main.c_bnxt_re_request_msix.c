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
struct bnxt_re_dev {int num_msix; int /*<<< orphan*/  msix_entries; struct bnxt_en_dev* en_dev; } ;
struct bnxt_en_dev {TYPE_1__* en_ops; } ;
struct TYPE_2__ {int (* bnxt_request_msix ) (struct bnxt_en_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int BNXT_RE_MAX_MSIX ; 
 int BNXT_RE_MIN_MSIX ; 
 int /*<<< orphan*/  BNXT_ROCE_ULP ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int,int) ; 
 int min_t (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  num_online_cpus () ; 
 int /*<<< orphan*/  rdev_to_dev (struct bnxt_re_dev*) ; 
 int stub1 (struct bnxt_en_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static int bnxt_re_request_msix(struct bnxt_re_dev *rdev)
{
	int rc = 0, num_msix_want = BNXT_RE_MAX_MSIX, num_msix_got;
	struct bnxt_en_dev *en_dev;

	if (!rdev)
		return -EINVAL;

	en_dev = rdev->en_dev;

	num_msix_want = min_t(u32, BNXT_RE_MAX_MSIX, num_online_cpus());

	num_msix_got = en_dev->en_ops->bnxt_request_msix(en_dev, BNXT_ROCE_ULP,
							 rdev->msix_entries,
							 num_msix_want);
	if (num_msix_got < BNXT_RE_MIN_MSIX) {
		rc = -EINVAL;
		goto done;
	}
	if (num_msix_got != num_msix_want) {
		dev_warn(rdev_to_dev(rdev),
			 "Requested %d MSI-X vectors, got %d\n",
			 num_msix_want, num_msix_got);
	}
	rdev->num_msix = num_msix_got;
done:
	return rc;
}