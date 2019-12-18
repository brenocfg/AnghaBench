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
struct TYPE_4__ {int pbl_size; int /*<<< orphan*/  pbl_addr; } ;
struct iwch_mr {TYPE_2__ attr; TYPE_1__* rhp; } ;
struct TYPE_3__ {int /*<<< orphan*/  rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxio_hal_pblpool_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void iwch_free_pbl(struct iwch_mr *mhp)
{
	cxio_hal_pblpool_free(&mhp->rhp->rdev, mhp->attr.pbl_addr,
			      mhp->attr.pbl_size << 3);
}