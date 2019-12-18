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
struct tid_info {int /*<<< orphan*/  ftid_lock; int /*<<< orphan*/  ftid_bmap; } ;

/* Variables and functions */
 unsigned int CHELSIO_T6 ; 
 int EBUSY ; 
 int PF_INET ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_allocate_region (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cxgb4_set_ftid(struct tid_info *t, int fidx, int family,
			  unsigned int chip_ver)
{
	spin_lock_bh(&t->ftid_lock);

	if (test_bit(fidx, t->ftid_bmap)) {
		spin_unlock_bh(&t->ftid_lock);
		return -EBUSY;
	}

	if (family == PF_INET) {
		__set_bit(fidx, t->ftid_bmap);
	} else {
		if (chip_ver < CHELSIO_T6)
			bitmap_allocate_region(t->ftid_bmap, fidx, 2);
		else
			bitmap_allocate_region(t->ftid_bmap, fidx, 1);
	}

	spin_unlock_bh(&t->ftid_lock);
	return 0;
}