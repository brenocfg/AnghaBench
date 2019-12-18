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
struct TYPE_2__ {int /*<<< orphan*/  mtt_buddy; int /*<<< orphan*/ * fmr_mtt_buddy; } ;
struct mthca_dev {int mthca_flags; TYPE_1__ mr_table; } ;

/* Variables and functions */
 int MTHCA_FLAG_FMR ; 
 int PAGE_SIZE ; 
 scalar_t__ mthca_is_memfree (struct mthca_dev*) ; 

int mthca_write_mtt_size(struct mthca_dev *dev)
{
	if (dev->mr_table.fmr_mtt_buddy != &dev->mr_table.mtt_buddy ||
	    !(dev->mthca_flags & MTHCA_FLAG_FMR))
		/*
		 * Be friendly to WRITE_MTT command
		 * and leave two empty slots for the
		 * index and reserved fields of the
		 * mailbox.
		 */
		return PAGE_SIZE / sizeof (u64) - 2;

	/* For Arbel, all MTTs must fit in the same page. */
	return mthca_is_memfree(dev) ? (PAGE_SIZE / sizeof (u64)) : 0x7ffffff;
}