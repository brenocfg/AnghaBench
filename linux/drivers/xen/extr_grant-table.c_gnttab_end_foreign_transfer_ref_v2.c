#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
typedef  size_t grant_ref_t ;
struct TYPE_8__ {TYPE_3__* v2; } ;
struct TYPE_5__ {unsigned long frame; } ;
struct TYPE_6__ {int flags; } ;
struct TYPE_7__ {TYPE_1__ full_page; TYPE_2__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int GTF_transfer_committed ; 
 int GTF_transfer_completed ; 
 int /*<<< orphan*/  cpu_relax () ; 
 TYPE_4__ gnttab_shared ; 
 int /*<<< orphan*/  rmb () ; 
 int sync_cmpxchg (int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long gnttab_end_foreign_transfer_ref_v2(grant_ref_t ref)
{
	unsigned long frame;
	u16           flags;
	u16          *pflags;

	pflags = &gnttab_shared.v2[ref].hdr.flags;

	/*
	 * If a transfer is not even yet started, try to reclaim the grant
	 * reference and return failure (== 0).
	 */
	while (!((flags = *pflags) & GTF_transfer_committed)) {
		if (sync_cmpxchg(pflags, flags, 0) == flags)
			return 0;
		cpu_relax();
	}

	/* If a transfer is in progress then wait until it is completed. */
	while (!(flags & GTF_transfer_completed)) {
		flags = *pflags;
		cpu_relax();
	}

	rmb();  /* Read the frame number /after/ reading completion status. */
	frame = gnttab_shared.v2[ref].full_page.frame;
	BUG_ON(frame == 0);

	return frame;
}