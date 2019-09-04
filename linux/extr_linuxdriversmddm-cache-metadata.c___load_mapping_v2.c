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
typedef  int /*<<< orphan*/  uint64_t ;
struct dm_cache_metadata {scalar_t__ clean_when_opened; } ;
struct dm_bitset_cursor {int dummy; } ;
struct dm_array_cursor {int dummy; } ;
typedef  int /*<<< orphan*/  mapping ;
typedef  int (* load_mapping_fn ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ;
typedef  int /*<<< orphan*/  hint ;
typedef  int /*<<< orphan*/  dm_oblock_t ;
typedef  int /*<<< orphan*/  __le64 ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*,unsigned long long) ; 
 unsigned int M_VALID ; 
 int /*<<< orphan*/  dm_array_cursor_get_value (struct dm_array_cursor*,void**) ; 
 int dm_bitset_cursor_get_value (struct dm_bitset_cursor*) ; 
 scalar_t__ from_cblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  to_cblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unpack_value (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int*) ; 

__attribute__((used)) static int __load_mapping_v2(struct dm_cache_metadata *cmd,
			     uint64_t cb, bool hints_valid,
			     struct dm_array_cursor *mapping_cursor,
			     struct dm_array_cursor *hint_cursor,
			     struct dm_bitset_cursor *dirty_cursor,
			     load_mapping_fn fn, void *context)
{
	int r = 0;

	__le64 mapping;
	__le32 hint = 0;

	__le64 *mapping_value_le;
	__le32 *hint_value_le;

	dm_oblock_t oblock;
	unsigned flags;
	bool dirty = true;

	dm_array_cursor_get_value(mapping_cursor, (void **) &mapping_value_le);
	memcpy(&mapping, mapping_value_le, sizeof(mapping));
	unpack_value(mapping, &oblock, &flags);

	if (flags & M_VALID) {
		if (hints_valid) {
			dm_array_cursor_get_value(hint_cursor, (void **) &hint_value_le);
			memcpy(&hint, hint_value_le, sizeof(hint));
		}
		if (cmd->clean_when_opened)
			dirty = dm_bitset_cursor_get_value(dirty_cursor);

		r = fn(context, oblock, to_cblock(cb), dirty,
		       le32_to_cpu(hint), hints_valid);
		if (r) {
			DMERR("policy couldn't load cache block %llu",
			      (unsigned long long) from_cblock(to_cblock(cb)));
		}
	}

	return r;
}