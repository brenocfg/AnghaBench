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
struct TYPE_3__ {int /*<<< orphan*/  mpt; } ;
struct TYPE_4__ {TYPE_1__ tavor; } ;
struct mthca_fmr {TYPE_2__ mem; scalar_t__ maps; } ;
struct mthca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTHCA_MPT_STATUS_SW ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mthca_tavor_fmr_unmap(struct mthca_dev *dev, struct mthca_fmr *fmr)
{
	if (!fmr->maps)
		return;

	fmr->maps = 0;

	writeb(MTHCA_MPT_STATUS_SW, fmr->mem.tavor.mpt);
}