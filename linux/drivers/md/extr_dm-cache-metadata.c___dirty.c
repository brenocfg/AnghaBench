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
struct dm_cache_metadata {int changed; int /*<<< orphan*/  root; int /*<<< orphan*/  info; } ;
typedef  int /*<<< orphan*/  dm_oblock_t ;
typedef  int /*<<< orphan*/  dm_cblock_t ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 unsigned int M_DIRTY ; 
 int /*<<< orphan*/  __dm_bless_for_disk (int /*<<< orphan*/ *) ; 
 int dm_array_get_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dm_array_set_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  from_cblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pack_value (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  unpack_value (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int*) ; 

__attribute__((used)) static int __dirty(struct dm_cache_metadata *cmd, dm_cblock_t cblock, bool dirty)
{
	int r;
	unsigned flags;
	dm_oblock_t oblock;
	__le64 value;

	r = dm_array_get_value(&cmd->info, cmd->root, from_cblock(cblock), &value);
	if (r)
		return r;

	unpack_value(value, &oblock, &flags);

	if (((flags & M_DIRTY) && dirty) || (!(flags & M_DIRTY) && !dirty))
		/* nothing to be done */
		return 0;

	value = pack_value(oblock, (flags & ~M_DIRTY) | (dirty ? M_DIRTY : 0));
	__dm_bless_for_disk(&value);

	r = dm_array_set_value(&cmd->info, cmd->root, from_cblock(cblock),
			       &value, &cmd->root);
	if (r)
		return r;

	cmd->changed = true;
	return 0;

}