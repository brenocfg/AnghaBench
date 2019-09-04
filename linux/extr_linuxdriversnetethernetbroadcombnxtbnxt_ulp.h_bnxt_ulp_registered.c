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
struct bnxt_en_dev {TYPE_1__* ulp_tbl; } ;
struct TYPE_2__ {int /*<<< orphan*/  ulp_ops; } ;

/* Variables and functions */
 scalar_t__ rcu_access_pointer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool bnxt_ulp_registered(struct bnxt_en_dev *edev, int ulp_id)
{
	if (edev && rcu_access_pointer(edev->ulp_tbl[ulp_id].ulp_ops))
		return true;
	return false;
}