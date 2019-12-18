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
typedef  unsigned int uint64_t ;
struct walk_info {int (* fn ) (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  info; int /*<<< orphan*/  context; } ;
struct dm_block {int dummy; } ;
struct array_block {int /*<<< orphan*/  nr_entries; int /*<<< orphan*/  max_entries; } ;
typedef  int /*<<< orphan*/  block_le ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  element_at (int /*<<< orphan*/ ,struct array_block*,unsigned int) ; 
 int get_ablock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dm_block**,struct array_block**) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,int) ; 
 int stub1 (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_ablock (int /*<<< orphan*/ ,struct dm_block*) ; 

__attribute__((used)) static int walk_ablock(void *context, uint64_t *keys, void *leaf)
{
	struct walk_info *wi = context;

	int r;
	unsigned i;
	__le64 block_le;
	unsigned nr_entries, max_entries;
	struct dm_block *block;
	struct array_block *ab;

	memcpy(&block_le, leaf, sizeof(block_le));
	r = get_ablock(wi->info, le64_to_cpu(block_le), &block, &ab);
	if (r)
		return r;

	max_entries = le32_to_cpu(ab->max_entries);
	nr_entries = le32_to_cpu(ab->nr_entries);
	for (i = 0; i < nr_entries; i++) {
		r = wi->fn(wi->context, keys[0] * max_entries + i,
			   element_at(wi->info, ab, i));

		if (r)
			break;
	}

	unlock_ablock(wi->info, block);
	return r;
}