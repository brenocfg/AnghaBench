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
typedef  int /*<<< orphan*/  uint32_t ;
struct cache_disk_superblock {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  (* flags_mutator ) (int /*<<< orphan*/ ) ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_flags(struct cache_disk_superblock *disk_super,
			 flags_mutator mutator)
{
	uint32_t sb_flags = mutator(le32_to_cpu(disk_super->flags));
	disk_super->flags = cpu_to_le32(sb_flags);
}