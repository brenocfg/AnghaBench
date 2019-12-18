#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ib_ucontext {int /*<<< orphan*/  device; } ;
struct hns_roce_ucontext {int /*<<< orphan*/  uar; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns_roce_uar_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_hr_dev (int /*<<< orphan*/ ) ; 
 struct hns_roce_ucontext* to_hr_ucontext (struct ib_ucontext*) ; 

__attribute__((used)) static void hns_roce_dealloc_ucontext(struct ib_ucontext *ibcontext)
{
	struct hns_roce_ucontext *context = to_hr_ucontext(ibcontext);

	hns_roce_uar_free(to_hr_dev(ibcontext->device), &context->uar);
}