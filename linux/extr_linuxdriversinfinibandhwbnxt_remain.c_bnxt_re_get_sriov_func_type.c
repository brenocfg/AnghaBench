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
struct bnxt_re_dev {int is_virtfn; TYPE_1__* en_dev; } ;
struct bnxt {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  net; } ;

/* Variables and functions */
 scalar_t__ BNXT_VF (struct bnxt*) ; 
 struct bnxt* netdev_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnxt_re_get_sriov_func_type(struct bnxt_re_dev *rdev)
{
	struct bnxt *bp;

	bp = netdev_priv(rdev->en_dev->net);
	if (BNXT_VF(bp))
		rdev->is_virtfn = 1;
}