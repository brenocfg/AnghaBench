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
struct dm_cache_metadata {int /*<<< orphan*/  discard_root; int /*<<< orphan*/  discard_info; } ;
typedef  int /*<<< orphan*/  dm_dblock_t ;

/* Variables and functions */
 int dm_bitset_set_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  from_dblock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __set_discard(struct dm_cache_metadata *cmd, dm_dblock_t b)
{
	return dm_bitset_set_bit(&cmd->discard_info, cmd->discard_root,
				 from_dblock(b), &cmd->discard_root);
}