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
struct dm_array_info {int dummy; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int insert_new_ablock (struct dm_array_info*,size_t,unsigned int,unsigned int,unsigned int,void const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int insert_full_ablocks(struct dm_array_info *info, size_t size_of_block,
			       unsigned begin_block, unsigned end_block,
			       unsigned max_entries, const void *value,
			       dm_block_t *root)
{
	int r = 0;

	for (; !r && begin_block != end_block; begin_block++)
		r = insert_new_ablock(info, size_of_block, max_entries, begin_block, max_entries, value, root);

	return r;
}