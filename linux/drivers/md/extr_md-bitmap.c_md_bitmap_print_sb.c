#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sb_page; } ;
struct bitmap {TYPE_1__ storage; } ;
struct TYPE_6__ {int /*<<< orphan*/  write_behind; int /*<<< orphan*/  sync_size; int /*<<< orphan*/  daemon_sleep; int /*<<< orphan*/  chunksize; int /*<<< orphan*/  state; int /*<<< orphan*/  events_cleared; int /*<<< orphan*/  events; scalar_t__ uuid; int /*<<< orphan*/  version; int /*<<< orphan*/  magic; } ;
typedef  TYPE_2__ bitmap_super_t ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 unsigned long long bmname (struct bitmap*) ; 
 TYPE_2__* kmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (TYPE_2__*) ; 
 unsigned long long le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long long,...) ; 

void md_bitmap_print_sb(struct bitmap *bitmap)
{
	bitmap_super_t *sb;

	if (!bitmap || !bitmap->storage.sb_page)
		return;
	sb = kmap_atomic(bitmap->storage.sb_page);
	pr_debug("%s: bitmap file superblock:\n", bmname(bitmap));
	pr_debug("         magic: %08x\n", le32_to_cpu(sb->magic));
	pr_debug("       version: %d\n", le32_to_cpu(sb->version));
	pr_debug("          uuid: %08x.%08x.%08x.%08x\n",
		 le32_to_cpu(*(__le32 *)(sb->uuid+0)),
		 le32_to_cpu(*(__le32 *)(sb->uuid+4)),
		 le32_to_cpu(*(__le32 *)(sb->uuid+8)),
		 le32_to_cpu(*(__le32 *)(sb->uuid+12)));
	pr_debug("        events: %llu\n",
		 (unsigned long long) le64_to_cpu(sb->events));
	pr_debug("events cleared: %llu\n",
		 (unsigned long long) le64_to_cpu(sb->events_cleared));
	pr_debug("         state: %08x\n", le32_to_cpu(sb->state));
	pr_debug("     chunksize: %d B\n", le32_to_cpu(sb->chunksize));
	pr_debug("  daemon sleep: %ds\n", le32_to_cpu(sb->daemon_sleep));
	pr_debug("     sync size: %llu KB\n",
		 (unsigned long long)le64_to_cpu(sb->sync_size)/2);
	pr_debug("max write behind: %d\n", le32_to_cpu(sb->write_behind));
	kunmap_atomic(sb);
}