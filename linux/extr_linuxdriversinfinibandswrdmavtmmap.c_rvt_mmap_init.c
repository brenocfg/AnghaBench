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
struct rvt_dev_info {int /*<<< orphan*/  mmap_offset_lock; int /*<<< orphan*/  mmap_offset; int /*<<< orphan*/  pending_lock; int /*<<< orphan*/  pending_mmaps; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void rvt_mmap_init(struct rvt_dev_info *rdi)
{
	INIT_LIST_HEAD(&rdi->pending_mmaps);
	spin_lock_init(&rdi->pending_lock);
	rdi->mmap_offset = PAGE_SIZE;
	spin_lock_init(&rdi->mmap_offset_lock);
}