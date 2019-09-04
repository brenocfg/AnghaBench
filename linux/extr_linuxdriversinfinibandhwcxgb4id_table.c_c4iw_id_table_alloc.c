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
typedef  int u32 ;
struct c4iw_id_table {int start; int flags; int last; int max; int /*<<< orphan*/  table; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_TO_LONGS (int) ; 
 int C4IW_ID_TABLE_F_EMPTY ; 
 int C4IW_ID_TABLE_F_RANDOM ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int RANDOM_SKIP ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kmalloc_array (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int prandom_u32 () ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int c4iw_id_table_alloc(struct c4iw_id_table *alloc, u32 start, u32 num,
			u32 reserved, u32 flags)
{
	int i;

	alloc->start = start;
	alloc->flags = flags;
	if (flags & C4IW_ID_TABLE_F_RANDOM)
		alloc->last = prandom_u32() % RANDOM_SKIP;
	else
		alloc->last = 0;
	alloc->max  = num;
	spin_lock_init(&alloc->lock);
	alloc->table = kmalloc_array(BITS_TO_LONGS(num), sizeof(long),
				     GFP_KERNEL);
	if (!alloc->table)
		return -ENOMEM;

	bitmap_zero(alloc->table, num);
	if (!(alloc->flags & C4IW_ID_TABLE_F_EMPTY))
		for (i = 0; i < reserved; ++i)
			set_bit(i, alloc->table);

	return 0;
}