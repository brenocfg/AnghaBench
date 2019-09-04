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
struct cached_dev {int /*<<< orphan*/  sb; int /*<<< orphan*/  has_dirty; } ;

/* Variables and functions */
 scalar_t__ BDEV_STATE (int /*<<< orphan*/ *) ; 
 scalar_t__ BDEV_STATE_DIRTY ; 
 int /*<<< orphan*/  SET_BDEV_STATE (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_xchg (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bch_write_bdev_super (struct cached_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bch_writeback_queue (struct cached_dev*) ; 

__attribute__((used)) static inline void bch_writeback_add(struct cached_dev *dc)
{
	if (!atomic_read(&dc->has_dirty) &&
	    !atomic_xchg(&dc->has_dirty, 1)) {
		if (BDEV_STATE(&dc->sb) != BDEV_STATE_DIRTY) {
			SET_BDEV_STATE(&dc->sb, BDEV_STATE_DIRTY);
			/* XXX: should do this synchronously */
			bch_write_bdev_super(dc, NULL);
		}

		bch_writeback_queue(dc);
	}
}