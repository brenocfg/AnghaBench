#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ib_pd {int /*<<< orphan*/  device; } ;
struct TYPE_3__ {int /*<<< orphan*/  pdn; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns_roce_pd_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  to_hr_dev (int /*<<< orphan*/ ) ; 
 TYPE_1__* to_hr_pd (struct ib_pd*) ; 

int hns_roce_dealloc_pd(struct ib_pd *pd)
{
	hns_roce_pd_free(to_hr_dev(pd->device), to_hr_pd(pd)->pdn);
	kfree(to_hr_pd(pd));

	return 0;
}