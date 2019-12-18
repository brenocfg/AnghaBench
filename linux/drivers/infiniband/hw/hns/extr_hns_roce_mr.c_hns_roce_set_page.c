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
typedef  int /*<<< orphan*/  u64 ;
struct ib_mr {int dummy; } ;
struct hns_roce_mr {int /*<<< orphan*/  npages; int /*<<< orphan*/ * pbl_buf; } ;

/* Variables and functions */
 struct hns_roce_mr* to_hr_mr (struct ib_mr*) ; 

__attribute__((used)) static int hns_roce_set_page(struct ib_mr *ibmr, u64 addr)
{
	struct hns_roce_mr *mr = to_hr_mr(ibmr);

	mr->pbl_buf[mr->npages++] = addr;

	return 0;
}