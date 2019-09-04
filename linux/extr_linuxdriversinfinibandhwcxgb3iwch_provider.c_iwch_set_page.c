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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {scalar_t__ pbl_size; } ;
struct iwch_mr {scalar_t__ npages; int /*<<< orphan*/ * pages; TYPE_1__ attr; } ;
struct ib_mr {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct iwch_mr* to_iwch_mr (struct ib_mr*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int iwch_set_page(struct ib_mr *ibmr, u64 addr)
{
	struct iwch_mr *mhp = to_iwch_mr(ibmr);

	if (unlikely(mhp->npages == mhp->attr.pbl_size))
		return -ENOMEM;

	mhp->pages[mhp->npages++] = addr;

	return 0;
}