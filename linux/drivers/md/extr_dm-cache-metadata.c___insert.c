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
 int /*<<< orphan*/  M_VALID ; 
 int /*<<< orphan*/  __dm_bless_for_disk (int /*<<< orphan*/ *) ; 
 int dm_array_set_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  from_cblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pack_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __insert(struct dm_cache_metadata *cmd,
		    dm_cblock_t cblock, dm_oblock_t oblock)
{
	int r;
	__le64 value = pack_value(oblock, M_VALID);
	__dm_bless_for_disk(&value);

	r = dm_array_set_value(&cmd->info, cmd->root, from_cblock(cblock),
			       &value, &cmd->root);
	if (r)
		return r;

	cmd->changed = true;
	return 0;
}