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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct bitmap {TYPE_1__ counts; } ;
typedef  int sector_t ;
typedef  int /*<<< orphan*/  bitmap_counter_t ;

/* Variables and functions */
 scalar_t__ NEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NEEDED_MASK ; 
 scalar_t__ RESYNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RESYNC_MASK ; 
 int /*<<< orphan*/ * md_bitmap_get_counter (TYPE_1__*,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __bitmap_start_sync(struct bitmap *bitmap, sector_t offset, sector_t *blocks,
			       int degraded)
{
	bitmap_counter_t *bmc;
	int rv;
	if (bitmap == NULL) {/* FIXME or bitmap set as 'failed' */
		*blocks = 1024;
		return 1; /* always resync if no bitmap */
	}
	spin_lock_irq(&bitmap->counts.lock);
	bmc = md_bitmap_get_counter(&bitmap->counts, offset, blocks, 0);
	rv = 0;
	if (bmc) {
		/* locked */
		if (RESYNC(*bmc))
			rv = 1;
		else if (NEEDED(*bmc)) {
			rv = 1;
			if (!degraded) { /* don't set/clear bits if degraded */
				*bmc |= RESYNC_MASK;
				*bmc &= ~NEEDED_MASK;
			}
		}
	}
	spin_unlock_irq(&bitmap->counts.lock);
	return rv;
}