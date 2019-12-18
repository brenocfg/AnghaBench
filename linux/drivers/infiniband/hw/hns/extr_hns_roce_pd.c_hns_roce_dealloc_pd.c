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
struct ib_udata {int dummy; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/  pdn; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns_roce_pd_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_hr_dev (int /*<<< orphan*/ ) ; 
 TYPE_1__* to_hr_pd (struct ib_pd*) ; 

void hns_roce_dealloc_pd(struct ib_pd *pd, struct ib_udata *udata)
{
	hns_roce_pd_free(to_hr_dev(pd->device), to_hr_pd(pd)->pdn);
}