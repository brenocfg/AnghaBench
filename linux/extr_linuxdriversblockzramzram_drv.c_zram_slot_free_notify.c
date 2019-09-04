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
struct TYPE_4__ {int /*<<< orphan*/  miss_free; int /*<<< orphan*/  notify_free; } ;
struct zram {TYPE_2__ stats; } ;
struct block_device {TYPE_1__* bd_disk; } ;
struct TYPE_3__ {struct zram* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zram_free_page (struct zram*,unsigned long) ; 
 int /*<<< orphan*/  zram_slot_trylock (struct zram*,unsigned long) ; 
 int /*<<< orphan*/  zram_slot_unlock (struct zram*,unsigned long) ; 

__attribute__((used)) static void zram_slot_free_notify(struct block_device *bdev,
				unsigned long index)
{
	struct zram *zram;

	zram = bdev->bd_disk->private_data;

	atomic64_inc(&zram->stats.notify_free);
	if (!zram_slot_trylock(zram, index)) {
		atomic64_inc(&zram->stats.miss_free);
		return;
	}

	zram_free_page(zram, index);
	zram_slot_unlock(zram, index);
}