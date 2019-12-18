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
struct stripe_head {int disks; int qd_idx; int pd_idx; struct r5dev* dev; scalar_t__ ddf_layout; } ;
struct r5dev {struct page* page; struct page* orig_page; int /*<<< orphan*/  flags; scalar_t__ written; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R5_InJournal ; 
 int /*<<< orphan*/  R5_Wantdrain ; 
 int SYNDROME_SRC_ALL ; 
 int SYNDROME_SRC_WANT_DRAIN ; 
 int SYNDROME_SRC_WRITTEN ; 
 int raid6_d0 (struct stripe_head*) ; 
 int raid6_idx_to_slot (int,struct stripe_head*,int*,int) ; 
 int raid6_next_disk (int,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int set_syndrome_sources(struct page **srcs,
				struct stripe_head *sh,
				int srctype)
{
	int disks = sh->disks;
	int syndrome_disks = sh->ddf_layout ? disks : (disks - 2);
	int d0_idx = raid6_d0(sh);
	int count;
	int i;

	for (i = 0; i < disks; i++)
		srcs[i] = NULL;

	count = 0;
	i = d0_idx;
	do {
		int slot = raid6_idx_to_slot(i, sh, &count, syndrome_disks);
		struct r5dev *dev = &sh->dev[i];

		if (i == sh->qd_idx || i == sh->pd_idx ||
		    (srctype == SYNDROME_SRC_ALL) ||
		    (srctype == SYNDROME_SRC_WANT_DRAIN &&
		     (test_bit(R5_Wantdrain, &dev->flags) ||
		      test_bit(R5_InJournal, &dev->flags))) ||
		    (srctype == SYNDROME_SRC_WRITTEN &&
		     (dev->written ||
		      test_bit(R5_InJournal, &dev->flags)))) {
			if (test_bit(R5_InJournal, &dev->flags))
				srcs[slot] = sh->dev[i].orig_page;
			else
				srcs[slot] = sh->dev[i].page;
		}
		i = raid6_next_disk(i, disks);
	} while (i != d0_idx);

	return syndrome_disks;
}